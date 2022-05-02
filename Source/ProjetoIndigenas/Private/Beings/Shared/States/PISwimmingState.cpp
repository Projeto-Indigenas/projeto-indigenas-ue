﻿#include "Beings/Shared/States/PISwimmingState.h"

#include <GameFramework/CharacterMovementComponent.h>

#include "WaterBodyActor.h"
#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Beings/Shared/PICharacterBase.h"
#include "GameFramework/PhysicsVolume.h"
#include "Misc/Logging.h"

bool FPISwimmingState::TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const
{
	const FVector& characterLocation = _character->GetActorLocation();

	const FWaterBodyQueryResult result = waterBodyActor->GetWaterBodyComponent()->QueryWaterInfoClosestToWorldLocation(
		characterLocation,
		EWaterBodyQueryFlags::ComputeDepth |
		EWaterBodyQueryFlags::ComputeImmersionDepth |
		EWaterBodyQueryFlags::ComputeLocation |
		EWaterBodyQueryFlags::ComputeNormal |
		EWaterBodyQueryFlags::ComputeVelocity);

	if (!result.IsInWater()) return false;
	
	info.WaterSurfaceLocation = result.GetWaterSurfaceLocation();
	info.WaterSurfaceNormal = result.GetWaterSurfaceNormal();
	info.WaterVelocity = result.GetVelocity();
	info.ImmersionDepth = result.GetImmersionDepth();

	return true;
}

void FPISwimmingState::SetVerticalInput(float movementSpeed)
{
	_movementSpeed = FMath::Max(0.f, movementSpeed);

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

void FPISwimmingState::CharacterMoveSwim(const float& deltaSeconds, const FRotator& cameraRotation)
{
	if (_swimAnimState == nullptr) return;

	_acceleratedCharacterDirection = FRotator(0.f, cameraRotation.Yaw, 0.f);
	_character->SetActorRelativeRotation(_acceleratedCharacterDirection);
	
	FVector swimDirection = cameraRotation.Vector();
	swimDirection.Normalize();

	const float& speed = _acceleratedMovementSpeed * 100.f * deltaSeconds; // meters / second
	
	FHitResult hit;
	_character->GetCharacterMovement()->Swim(swimDirection * speed, hit);
}

FPISwimmingState::FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData>(character, stateData)
{
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;
	_acceleratedCharacterDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedSwimAnimDirection.SetAcceleration(stateData.RotationAcceleration);
}

void FPISwimmingState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPISwimmingState::SetVerticalInput);
	inputDelegates.CameraRotatorDelegate.BindRaw(this, &FPISwimmingState::SetCameraRotator);
	inputDelegates.ToggleRunDelegate.BindRaw(this, &FPISwimmingState::SetFastSwim);
	
	if (!_character.IsValid()) return;

	UPICharacterAnimInstance* animInstance = _character->GetAnimInstance<UPICharacterAnimInstance>();
	_characterAnimState = &animInstance->State;
	_swimAnimState = &animInstance->SwimAnimState;
	*_characterAnimState = EPICharacterAnimationState::Swimming;

	_acceleratedCharacterDirection.SetCurrent(_character->GetActorRotation());

	WaterBody->GetPhysicsVolume()->bWaterVolume = true;
	_character->GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
}

void FPISwimmingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPISwimmingStateBase::Exit(inputDelegates, onExitDelegate);

	inputDelegates.VerticalInputDelegate.Unbind();
	inputDelegates.CameraRotatorDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();
	
	if (_characterAnimState != nullptr)
	{
		*_characterAnimState = EPICharacterAnimationState::Default;
	}
	
	_characterAnimState = nullptr;
	_swimAnimState = nullptr;

	_character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

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
	if (!TryGetWaterBodyInfo(WaterBody.Get(), info)) return;

	const FVector& characterLocation = _character->GetActorLocation();
	const float& distanceFromSurface = FMath::Abs(FVector::Distance(info.WaterSurfaceLocation, characterLocation));
	const float& underwaterCharacterThreshold = info.WaterSurfaceLocation.Z - _swimUnderwaterThreshold;

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
	CharacterMoveSwim(DeltaSeconds, _cameraRotator);

	FString mode;
	switch (_character->GetCharacterMovement()->MovementMode.GetValue())
	{
	case MOVE_Walking:
		mode = TEXT("Walking");
		break;
	case MOVE_Swimming:
		mode = TEXT("Swimming");
		break;
	case MOVE_Flying:
		mode = TEXT("Flying");
		break;
	case MOVE_Custom:
		mode = TEXT("Custom");
		break;
	case MOVE_Falling:
		mode = TEXT("Falling");
		break;
	case MOVE_NavWalking:
		mode = TEXT("NavWalking");
		break;
	case MOVE_None:
		mode = TEXT("None");
	default:
		mode = TEXT("Unknown");
		break;
	}
	
	PI_SCREEN_LOG(100, 1.f, TEXT("MovementMode: %s"), *mode)

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

	return _character->GetActorLocation().Z <= info.WaterSurfaceLocation.Z;
}

bool FPISwimmingState::CanEndSwimming(const AWaterBody* waterBodyActor)
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
	
	return _character->GetCharacterMovement()->MovementMode != MOVE_Swimming;
}