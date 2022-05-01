#include "Beings/Shared/States/PIMovementState.h"

#include <Components/CapsuleComponent.h>
#include <Kismet/KismetMathLibrary.h>

#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Beings/Shared/PICharacterBase.h"
#include "Misc/Logging.h"

void FPIMovementState::UpdateMovementSpeed()
{
	_inputVector.Z = 0.f;
	if (_inputVector == FVector::ZeroVector) _run = false;
	const float runMultiplier = _run ? 2.f : 1.f;
	_acceleratedMovementSpeed = _inputVector.GetClampedToMaxSize(1.f).Size() * runMultiplier;
}

void FPIMovementState::SetXInput(float x)
{
	_inputVector.Y = x;

	UpdateMovementSpeed();
}

void FPIMovementState::SetYInput(float y)
{
	_inputVector.X = y;

	UpdateMovementSpeed();
}

void FPIMovementState::ToggleRun()
{
	_run = !_run;

	UpdateMovementSpeed();
}

void FPIMovementState::SetDirectionYaw(float directionYaw)
{
	_directionYaw = directionYaw;
}

void FPIMovementState::Dodge() const
{
	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	
	if (animInstance == nullptr) return;

	animInstance->ShouldDodge = true;
}

void FPIMovementState::OnTurnStarted()
{
	_isTurning = true;
}

void FPIMovementState::OnTurnEnded()
{
	_isTurning = false;

	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	if (animInstance != nullptr)
	{
		animInstance->MovementDirectionAngle = 0.f;
	}
	
	if (_character.IsValid())
	{
		_acceleratedCharacterDirection.SetCurrent(_character->GetActorRotation().Vector());
	}
}

FPIMovementState::FPIMovementState(APICharacterBase* character, const FPIMovementStateData& stateData):
	FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPIMovementStateData>(character, stateData)
{
	_acceleratedCharacterDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;

	_acceleratedCapsuleRadius.Acceleration = stateData.CapsuleRadiusAcceleration;
}

void FPIMovementState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.HorizontalInputDelegate.BindRaw(this, &FPIMovementState::SetXInput);
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPIMovementState::SetYInput);
	inputDelegates.DirectionYawDelegate.BindRaw(this, &FPIMovementState::SetDirectionYaw);
	inputDelegates.ToggleRunDelegate.BindRaw(this, &FPIMovementState::ToggleRun);
	inputDelegates.DodgeDelegate.BindRaw(this, &FPIMovementState::Dodge);

	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	if (animInstance != nullptr)
	{
		animInstance->TurnStartedDelegate.BindRaw(this, &FPIMovementState::OnTurnStarted);
		animInstance->TurnEndedDelegate.BindRaw(this, &FPIMovementState::OnTurnEnded);
	}
	
	_acceleratedCapsuleRadius.Current = _capsuleComponent->GetScaledCapsuleRadius();
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;

	if (_character.IsValid())
	{
		const FVector& currentCharacterDirection = _character->GetActorRotation().Vector();
		_acceleratedCharacterDirection.SetCurrent(currentCharacterDirection);
		_acceleratedCharacterDirection = currentCharacterDirection;
	}
}

void FPIMovementState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPIMovementStateBase::Exit(inputDelegates, onExitDelegate);
	
	inputDelegates.HorizontalInputDelegate.Unbind();
	inputDelegates.VerticalInputDelegate.Unbind();
	inputDelegates.DirectionYawDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();
	inputDelegates.DodgeDelegate.Unbind();

	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	if (animInstance != nullptr)
	{
		animInstance->TurnStartedDelegate.Unbind();
		animInstance->TurnEndedDelegate.Unbind();
		animInstance->MovementSpeed = 0.f;
	}

	_inputVector = FVector::ZeroVector;
	_run = false;
	
	InvokeOnExitDelegate();
}

void FPIMovementState::Tick(float DeltaSeconds)
{
	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	
	if (!_isTurning)
	{
		_acceleratedCharacterDirection.Tick(DeltaSeconds);
		_acceleratedCapsuleRadius.Tick(DeltaSeconds);
		_acceleratedMovementSpeed.Tick(DeltaSeconds);
	
		if (!_character.IsValid()) return;
		if (!_capsuleComponent.IsValid()) return;

		if (animInstance != nullptr)
		{
			animInstance->MovementSpeed = _acceleratedMovementSpeed;
		}
	
		_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	
		if (_inputVector != FVector::ZeroVector)
		{
			const FRotator& cameraRotator = FRotator(0.f, _directionYaw, 0.f);
			_acceleratedCharacterDirection = cameraRotator.Vector();
			const FRotator& currentDirectionRotator = _acceleratedCharacterDirection;
			_character->SetActorRelativeRotation(currentDirectionRotator);
		}
	}

	if (animInstance != nullptr)
	{
		const float& foundAngle = FMath::FindDeltaAngleDegrees(
		_acceleratedCharacterDirection.GetTargetRotator().Yaw,
		FRotator(_acceleratedCharacterDirection).Yaw);
		animInstance->MovementDirectionAngle = FMath::Abs(foundAngle);
	}

#if !UE_BUILD_SHIPPING
	_logKey = 0;
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("Anim Movement Speed: %f"),
		animInstance->MovementSpeed)
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("Anim Direction Angle: %f"),
		animInstance->MovementDirectionAngle)
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("InputVector Yaw: %f"), _inputVector.Rotation().Yaw)
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("DirectionYaw: %f"), _directionYaw)
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("AccDir Current: %f"),
		FRotator(_acceleratedCharacterDirection).Yaw)
	PI_SCREEN_LOGV(_movementStateScreenLogs, 1.0, TEXT("AccDir Target: %f"),
		_acceleratedCharacterDirection.GetTargetRotator().Yaw)
#endif
}





