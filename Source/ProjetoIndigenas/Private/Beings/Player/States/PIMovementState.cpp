#include "Beings/Player/States/PIMovementState.h"

#include <Components/CapsuleComponent.h>
#include <Kismet/KismetMathLibrary.h>

#include "Beings/Shared/PIAnimInstanceBase.h"

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
	FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIMovementStateData>(character, stateData),
	_run(false),
	_directionYaw(0)
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

	_acceleratedCapsuleRadius.SetNow(_capsuleComponent->GetUnscaledCapsuleRadius());
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;
}

void FPIMovementState::Exit(FPIInputDelegates& inputDelegates)
{
	inputDelegates.HorizontalInputDelegate.Unbind();
	inputDelegates.VerticalInputDelegate.Unbind();
	inputDelegates.DirectionYawDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();
	inputDelegates.DodgeDelegate.Unbind();

	_inputVector = FVector::ZeroVector;
	_run = false;
}

void FPIMovementState::Tick(float DeltaSeconds)
{
	_acceleratedCharacterDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);
	
	if (!_character.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;

	APICharacterBase* character = _character.Get();
	UPICharacterAnimInstance* animInstance = _animInstance.Get();
	UCapsuleComponent* capsuleComponent = _capsuleComponent.Get();
	
	capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);

	animInstance->MovementSpeed = _acceleratedMovementSpeed;

	if (_inputVector == FVector::ZeroVector) return;
	
	const FRotator cameraRotator(0.f, _directionYaw, 0.f);
	const FRotator inputRotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, _inputVector);
	const FRotator targetRotator = cameraRotator + inputRotator;
		
	_acceleratedCharacterDirection = targetRotator.Vector();
		
	character->SetActorRelativeRotation(_acceleratedCharacterDirection);
}





