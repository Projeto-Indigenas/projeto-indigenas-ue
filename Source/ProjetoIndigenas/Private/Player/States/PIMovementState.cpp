﻿#include "Player/States/PIMovementState.h"

#include <Components/CapsuleComponent.h>
#include <Kismet/KismetMathLibrary.h>

#include "Player/PIAnimInstanceBase.h"

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
	if (!_animInstance.IsValid()) return;

	_animInstance->ShouldDodge = true;
}

FPIMovementState::FPIMovementState(APICharacterBase* character, const FPIMovementStateData& stateData):
	FPIStateBaseWithData(character, stateData),
	_run(false),
	_directionYaw(0)
{
	_acceleratedCharacterDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;

	_acceleratedCapsuleRadius = FAcceleratedValue(stateData.CapsuleRadius, stateData.CapsuleRadiusAcceleration);
}

void FPIMovementState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.InputHorizontalDelegate.BindRaw(this, &FPIMovementState::SetXInput);
	inputDelegates.InputVerticalDelegate.BindRaw(this, &FPIMovementState::SetYInput);
	inputDelegates.DirectionYawDelegate.BindRaw(this, &FPIMovementState::SetDirectionYaw);
	inputDelegates.ToggleRunDelegate.BindRaw(this, &FPIMovementState::ToggleRun);
	inputDelegates.DodgeDelegate.BindRaw(this, &FPIMovementState::Dodge);
}

void FPIMovementState::Exit(FPIInputDelegates& inputDelegates)
{
	inputDelegates.InputHorizontalDelegate.Unbind();
	inputDelegates.InputVerticalDelegate.Unbind();
	inputDelegates.DirectionYawDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();
	inputDelegates.DodgeDelegate.Unbind();
}

void FPIMovementState::Tick(float DeltaSeconds)
{
	_acceleratedCharacterDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);

	if (_capsuleComponent.IsValid())
	{
		_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	}

	if (_animInstance.IsValid())
	{
		_animInstance->MovementSpeed = _acceleratedMovementSpeed;
	}

	if (_inputVector != FVector::ZeroVector)
	{
		const FRotator cameraRotator(0.f, _directionYaw, 0.f);
		const FRotator inputRotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, _inputVector);
		const FRotator targetRotator = cameraRotator + inputRotator;
		
		_acceleratedCharacterDirection = targetRotator.Vector();
		
		_character->SetActorRelativeRotation(_acceleratedCharacterDirection);
	}
}





