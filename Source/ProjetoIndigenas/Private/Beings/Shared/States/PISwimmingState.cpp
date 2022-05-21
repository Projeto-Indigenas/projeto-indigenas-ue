#include "Beings/Shared/States/PISwimmingState.h"

#include <GameFramework/CharacterMovementComponent.h>

#include "Landscape.h"
#include "WaterBodyActor.h"
#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Beings/Shared/PICharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Logging.h"

#define PI_LOGGING_TYPE_NAME() TEXT("FPISwimmingState")

bool FPISwimmingState::TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const
{
	const FVector& characterLocation = _character->GetActorLocation();

	const FWaterBodyQueryResult result = waterBodyActor->GetWaterBodyComponent()->QueryWaterInfoClosestToWorldLocation(
		characterLocation,
		EWaterBodyQueryFlags::ComputeDepth |
		EWaterBodyQueryFlags::ComputeImmersionDepth |
		EWaterBodyQueryFlags::ComputeLocation |
		EWaterBodyQueryFlags::ComputeNormal |
		EWaterBodyQueryFlags::ComputeVelocity |
		EWaterBodyQueryFlags::IncludeWaves);
	
	info.WaterSurfaceLocation = result.GetWaterSurfaceLocation();
	info.WaterSurfaceNormal = result.GetWaterSurfaceNormal();
	info.WaterVelocity = result.GetVelocity();
	info.ImmersionDepth = result.GetImmersionDepth();
	info.IsInWater = result.IsInWater();
	info.WaveHeight = result.GetWaveInfo().Height;
	info.WaveNormal = result.GetWaveInfo().Normal;

	return true;
}

bool FPISwimmingState::IsReturnToWaterCooldownDue() const
{
	const float& now = UGameplayStatics::GetTimeSeconds(_character->GetWorld());
	return now - _getOutOfWaterTime > _returnToWaterCooldownTime;
}

float FPISwimmingState::GetWaterSurfaceHeight(const FPIWaterBodyInfo& info)
{
	return info.WaterSurfaceLocation.Z;
}

void FPISwimmingState::UpdateHasLandBellowFeet()
{
	const float& characterHalfHeight = _character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const FVector& characterFeetLocation = _character->GetActorLocation() + FVector::DownVector * characterHalfHeight;
	const FVector& endLocation = characterFeetLocation + FVector::DownVector * 50.f;

#if !UE_BUILD_SHIPPING
	DrawDebugLine(_character->GetWorld(), characterFeetLocation, endLocation, FColor::Emerald);
#endif
	
	FHitResult hit;
	FCollisionQueryParams params(TEXT(""), false);
	params.AddIgnoredActor(_character.Get());
	params.AddIgnoredActor(WaterBody.Get());
	if (_character->GetWorld()->LineTraceSingleByChannel(
		hit, characterFeetLocation, endLocation, ECC_WorldStatic, params))
	{
		_hasLandBellowFeet = hit.GetActor() != nullptr;
		
		return;
	}

	_hasLandBellowFeet = false;
}

void FPISwimmingState::SetVerticalInput(float movementSpeed)
{
	_movementSpeed = FMath::Clamp(movementSpeed, 0.f, 1.f);

	UpdateMovementSpeed();
}

void FPISwimmingState::SetCameraRotator(FRotator cameraRotator)
{
	_cameraRotator = cameraRotator;	
}

void FPISwimmingState::SetFastSwim()
{
	_fastSwim = !_fastSwim;
	
	UpdateMovementSpeed();
}

void FPISwimmingState::UpdateMovementSpeed()
{
	_acceleratedMovementSpeed = _fastSwim ? _movementSpeed * 2.f : _movementSpeed;
}

void FPISwimmingState::CalculateSwimDirection(const FRotator& targetRotation)
{
	const float& horizontalSwim = FMath::Clamp(targetRotation.Yaw, -_horizontalLimit, _horizontalLimit) / _horizontalLimit;
	const float& verticalSwim = FMath::Clamp(targetRotation.Pitch, -_verticalLimit, _verticalLimit) / _verticalLimit;
	const FVector2D& swimDirection = FVector2D(horizontalSwim, verticalSwim);
	_acceleratedSwimAnimDirection = swimDirection;
	
	if (_swimAnimState == nullptr) return;
	_swimAnimState->SwimDirection = _acceleratedSwimAnimDirection;
}

void FPISwimmingState::CharacterMoveSwim(const FRotator& cameraRotation)
{
	if (_swimAnimState == nullptr) return;

	_acceleratedCharacterDirection = FRotator(0.f, cameraRotation.Yaw, 0.f);
	_character->SetActorRelativeRotation(_acceleratedCharacterDirection);
	
	FVector swimDirection = cameraRotation.Vector();
	swimDirection.Normalize();

	_character->GetCharacterMovement()->MaxSwimSpeed = _acceleratedMovementSpeed * 100.f;
	_character->AddMovementInput(swimDirection);
}

void FPISwimmingState::ConstraintToWater(const FPIWaterBodyInfo& info) const
{
	if (!IsReturnToWaterCooldownDue()) return;
	if (_hasLandBellowFeet) return;

	FVector characterLocation = _character->GetActorLocation();
	const float& maxHeight = GetWaterSurfaceHeight(info) - _swimSurfaceThreshold;
	characterLocation.Z = FMath::Min(characterLocation.Z, maxHeight);
	_character->SetActorLocation(characterLocation);
}

FPISwimmingState::FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData>(character, stateData)
{
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;
	_acceleratedCharacterDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedSwimAnimDirection.SetAcceleration(stateData.RotationAcceleration);
}

void FPISwimmingState::BindInput(const TSharedRef<FPIInputDelegates>& inputDelegates)
{
	inputDelegates->VerticalInputDelegate.BindRaw(this, &FPISwimmingState::SetVerticalInput);
	inputDelegates->CameraRotatorDelegate.BindRaw(this, &FPISwimmingState::SetCameraRotator);
	inputDelegates->ToggleRunDelegate.BindRaw(this, &FPISwimmingState::SetFastSwim);
}

void FPISwimmingState::UnbindInput(const TSharedRef<FPIInputDelegates>& inputDelegates)
{
	inputDelegates->VerticalInputDelegate.Unbind();
	inputDelegates->CameraRotatorDelegate.Unbind();
	inputDelegates->ToggleRunDelegate.Unbind();
}

void FPISwimmingState::Enter()
{
	if (!_character.IsValid()) return;

	UPICharacterAnimInstance* animInstance = _character->GetAnimInstance<UPICharacterAnimInstance>();
	_characterAnimState = &animInstance->State;
	_swimAnimState = &animInstance->SwimAnimState;
	*_characterAnimState = EPICharacterAnimationState::Swimming;

	_acceleratedCharacterDirection.SetCurrent(_character->GetActorRotation());

	WaterBody->GetPhysicsVolume()->bWaterVolume = true;
	_character->GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
}

void FPISwimmingState::Exit(FPIStateOnExitDelegate onExitDelegate)
{
	FPISwimmingStateBase::Exit(onExitDelegate);

	_character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
	if (_characterAnimState != nullptr)
	{
		*_characterAnimState = EPICharacterAnimationState::Default;
	}

	_getOutOfWaterTime = UGameplayStatics::GetTimeSeconds(_character->GetWorld());
	
	_characterAnimState = nullptr;
	_swimAnimState = nullptr;

	InvokeOnExitDelegate();
}

void FPISwimmingState::Tick(float DeltaSeconds)
{
	FPISwimmingStateBase::Tick(DeltaSeconds);

	_acceleratedMovementSpeed.Tick(DeltaSeconds);
	_acceleratedCharacterDirection.Tick(DeltaSeconds);
	_acceleratedSwimAnimDirection.Tick(DeltaSeconds);

	if (!WaterBody.IsValid()) return;
	if (!_character.IsValid()) return;
	
	UPICharacterAnimInstance* animInstance = _character->GetAnimInstance<UPICharacterAnimInstance>();

	if (animInstance == nullptr) return;
	
	FPIWaterBodyInfo info;
	if (TryGetWaterBodyInfo(WaterBody.Get(), info))
	{
		_waterBodyInfo = MakeShared<FPIWaterBodyInfo>(info);
	}
	else
	{
		_waterBodyInfo.Reset();
		
		return;
	}

	const FVector& characterLocation = _character->GetActorLocation();
	const float& distanceFromSurface = FMath::Abs(FVector::Distance(info.WaterSurfaceLocation, characterLocation));
	const float& underwaterCharacterThreshold = GetWaterSurfaceHeight(info) - _swimUnderwaterThreshold;

	if (_swimAnimState != nullptr)
	{
		_swimAnimState->IsAtSurface = characterLocation.Z > underwaterCharacterThreshold;
	}

	animInstance->MovementSpeed = _acceleratedMovementSpeed;

	const FRotator& characterRotation = _character->GetActorRotation();
	_cameraRotator - characterRotation;
	const FRotator& targetRotation = FRotator(
		FMath::FindDeltaAngleDegrees(characterRotation.Pitch, _cameraRotator.Pitch),
		FMath::FindDeltaAngleDegrees(characterRotation.Yaw, _cameraRotator.Yaw),
		0.f
	);

	CalculateSwimDirection(targetRotation);
	CharacterMoveSwim(_cameraRotator);
	UpdateHasLandBellowFeet();
	ConstraintToWater(info);

#if !UE_BUILD_SHIPPING
	if (_swimmingLogsEnabled.GetValueOnGameThread())
	{
		DrawDebugLine(_character->GetWorld(),
			info.WaterSurfaceLocation,
			info.WaterSurfaceLocation + FVector::UpVector * 100.f,
			FColor::Red);
		DrawDebugLine(_character->GetWorld(),
			info.WaterSurfaceLocation,
			info.WaterSurfaceLocation + info.WaterSurfaceNormal * 50.f,
			FColor::Blue);
		FVector waterVelocityNormalized = info.WaterVelocity;
		waterVelocityNormalized.Normalize();
		DrawDebugLine(_character->GetWorld(),
			info.WaterSurfaceLocation,
			info.WaterSurfaceLocation + waterVelocityNormalized * 100.f,
			FColor::Green);

		FVector waveLocation = info.WaterSurfaceLocation;
		DrawDebugSphere(_character->GetWorld(), info.WaterSurfaceLocation, 1.f, 5, FColor::Red);
		waveLocation.Z = GetWaterSurfaceHeight(info);
		DrawDebugSphere(_character->GetWorld(), waveLocation, 1.f, 5, FColor::Orange);
	}
	
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water depth: %f"), info.ImmersionDepth)
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water velocity: %s"), *info.WaterVelocity.ToString())
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water surface location: %s"), *info.WaterSurfaceLocation.ToString())
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water surface normal: %s"), *info.WaterSurfaceNormal.ToString())

	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Distance from surface: %f"), distanceFromSurface)
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Character height threshold: %f"), underwaterCharacterThreshold)

	if (_swimAnimState != nullptr)
	{
		PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Swim direction: %s"), *_swimAnimState->SwimDirection.ToString())
	}

	_logKey = 0;
#endif
}

bool FPISwimmingState::CanStartSwimming(const AWaterBody* waterBodyActor) const
{
	if (!IsReturnToWaterCooldownDue()) return false;
	
	if (!_character.IsValid())
	{
		PI_LOGV(Error, TEXT("Cannot check for swimming without a character"))

		return false;
	}

	if (waterBodyActor == nullptr) return false;

	FPIWaterBodyInfo info;
	if (!TryGetWaterBodyInfo(waterBodyActor, info)) return false;

	return _character->GetActorLocation().Z <= GetWaterSurfaceHeight(info);
}

bool FPISwimmingState::CanEndSwimming() const
{
	if (!_character.IsValid())
	{
		PI_LOGV(Error, TEXT("Cannot check for swimming without a character"))

		return false;
	}
	
	if (!_waterBodyInfo.IsValid()) return false;
	
	return _hasLandBellowFeet && _character->GetActorLocation().Z >= GetWaterSurfaceHeight(*_waterBodyInfo);
}
