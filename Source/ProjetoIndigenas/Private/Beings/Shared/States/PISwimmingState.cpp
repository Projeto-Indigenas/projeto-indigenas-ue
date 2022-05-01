#include "Beings/Shared/States/PISwimmingState.h"

#include <GameFramework/CharacterMovementComponent.h>

#include "Components/CapsuleComponent.h"

#include "WaterBodyActor.h"
#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Misc/Logging.h"
#include "Beings/Shared/PICharacterBase.h"

bool FPISwimmingState::TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const
{
	const FVector& characterLocation = _character->GetActorLocation();

	const FWaterBodyQueryResult result = waterBodyActor->GetWaterBodyComponent()->QueryWaterInfoClosestToWorldLocation(
		characterLocation,
		EWaterBodyQueryFlags::ComputeImmersionDepth |
		EWaterBodyQueryFlags::ComputeLocation |
		EWaterBodyQueryFlags::ComputeNormal |
		EWaterBodyQueryFlags::ComputeVelocity);

	if (!result.IsInWater()) return false;
	
	info.WaterSurfaceLocation = result.GetWaterSurfaceLocation();
	info.WaterSurfaceNormal = result.GetWaterSurfaceNormal();
	info.WaterVelocity = result.GetVelocity();
	info.WaterDepth = result.GetImmersionDepth();

	return true;
}

void FPISwimmingState::SetVerticalInput(float movementSpeed)
{
	_movementSpeed = movementSpeed;

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

FPISwimmingState::FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData>(character, stateData)
{
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;
	_acceleratedDirection.SetAcceleration(stateData.RotationAcceleration);
}

void FPISwimmingState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPISwimmingState::SetVerticalInput);
	inputDelegates.CameraRotatorDelegate.BindRaw(this, &FPISwimmingState::SetCameraRotator);
	inputDelegates.ToggleRunDelegate.BindRaw(this, &FPISwimmingState::SetFastSwim);
	
	if (!_character.IsValid()) return;

	UPICharacterAnimInstance* animInstance = _character->GetAnimInstance<UPICharacterAnimInstance>();
	animInstance->State = EPICharacterAnimationState::Swimming;

	_acceleratedRotation.SetCurrent(_character->GetActorForwardVector());
	_character->GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
}

void FPISwimmingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPISwimmingStateBase::Exit(inputDelegates, onExitDelegate);

	inputDelegates.VerticalInputDelegate.Unbind();
	inputDelegates.DirectionYawDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();

	InvokeOnExitDelegate();
}

void FPISwimmingState::Tick(float DeltaSeconds)
{
	FPISwimmingStateBase::Tick(DeltaSeconds);

	_acceleratedMovementSpeed.Tick(DeltaSeconds);
	_acceleratedDirection.Tick(DeltaSeconds);
	_acceleratedRotation.Tick(DeltaSeconds);

	if (!WaterBody.IsValid()) return;
	if (!_character.IsValid()) return;

	UPICharacterAnimInstance* animInstance = _character->GetAnimInstance<UPICharacterAnimInstance>();

	if (animInstance == nullptr) return;
	
	FPIWaterBodyInfo info;
	if (!TryGetWaterBodyInfo(WaterBody.Get(), info)) return;

	const FVector& characterLocation = _character->GetActorLocation();
	const float& distanceFromSurface = FMath::Abs(FVector::Distance(info.WaterSurfaceLocation, characterLocation));
	const float& characterHeight = _character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const float& underwaterCharacterThreshold = characterHeight * _underwaterThreshold;
	
	animInstance->MovementSpeed = _acceleratedMovementSpeed;
	animInstance->SwimAnimState.IsAtSurface = distanceFromSurface < underwaterCharacterThreshold;

	FVector swimDirection = _character->GetActorForwardVector();
	const FVector& directionVector = _cameraRotator.Vector();

	const float& deltaAngleYaw = FMath::FindDeltaAngleDegrees(
		swimDirection.Rotation().Yaw, directionVector.Rotation().Yaw);
	const float& deltaAngleRoll = FMath::FindDeltaAngleDegrees(
		swimDirection.Rotation().Pitch, directionVector.Rotation().Pitch);
	FVector deltaDirectionVector = FVector(deltaAngleYaw/90.f, deltaAngleRoll/90.f, 0.f).GetClampedToMaxSize(1.f);
	
	animInstance->SwimAnimState.SwimDirection = FVector2D(deltaDirectionVector.X, deltaDirectionVector.Y);

	_acceleratedRotation.Y = swimDirection.Rotation().Yaw;
	
	const float& speed = _acceleratedMovementSpeed * 100.f * DeltaSeconds; // meters / second
	FHitResult result;
	swimDirection.Z = deltaDirectionVector.Y;
	_character->GetCharacterMovement()->Swim(swimDirection * speed, result);
	_character->SetActorRotation(_acceleratedRotation);

#if !UE_BUILD_SHIPPING
	_logKey = 0;
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

		DrawDebugLine(_character->GetWorld(),
			characterLocation, characterLocation + swimDirection * 100.f,
			FColor::Orange);
		DrawDebugLine(_character->GetWorld(),
			characterLocation, characterLocation + directionVector * 100.f,
			FColor::Purple);
		DrawDebugLine(_character->GetWorld(),
			characterLocation, characterLocation + deltaDirectionVector * 100.f,
			FColor::Cyan);
	}
	
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water depth: %f"), info.WaterDepth)
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water velocity: %s"), *info.WaterVelocity.ToString())
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water surface location: %s"), *info.WaterSurfaceLocation.ToString())
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Water surface normal: %s"), *info.WaterSurfaceNormal.ToString())

	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Distance from surface: %f"), distanceFromSurface)
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Character height threshold: %f"), underwaterCharacterThreshold)
	
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Swim direction: %s"), *swimDirection.ToString())
	PI_SCREEN_LOGV(_swimmingLogsEnabled, 1.f, TEXT("Swim speed: %f"), speed)
#endif
}

bool FPISwimmingState::CanStartSwimming(const AWaterBody* waterBodyActor)
{
	if (!_character.IsValid())
	{
		PI_LOGV(Error, TEXT("Cannot check for swimming without a character"))

		return false;
	}

	if (waterBodyActor == nullptr)
	{
		PI_LOGV(Error, TEXT("Calling swim check without water body actor"))

		return false;
	}
	
	FPIWaterBodyInfo info;
	if (!TryGetWaterBodyInfo(waterBodyActor, info)) return false;

	const float& characterHeight = _character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	// TODO(anderson): define this percentage somewhere configurable
	return info.WaterDepth >= characterHeight * _enterSwimThreshold;
}
