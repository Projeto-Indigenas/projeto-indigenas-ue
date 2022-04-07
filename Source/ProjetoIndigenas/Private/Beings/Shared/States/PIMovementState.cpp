#include "Beings/Shared/States/PIMovementState.h"

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
	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	
	if (animInstance == nullptr) return;

	animInstance->ShouldDodge = true;
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

	_acceleratedCapsuleRadius.Current = _capsuleComponent->GetScaledCapsuleRadius();
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;
}

void FPIMovementState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPIMovementStateBase::Exit(inputDelegates, onExitDelegate);
	
	inputDelegates.HorizontalInputDelegate.Unbind();
	inputDelegates.VerticalInputDelegate.Unbind();
	inputDelegates.DirectionYawDelegate.Unbind();
	inputDelegates.ToggleRunDelegate.Unbind();
	inputDelegates.DodgeDelegate.Unbind();

	_inputVector = FVector::ZeroVector;
	_run = false;

	InvokeOnExitDelegate();
}

void FPIMovementState::Tick(float DeltaSeconds)
{
	_acceleratedCharacterDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);

	UPIAnimInstanceBase* animInstance = GetAnimInstance();
	
	if (!_character.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;
	if (animInstance == nullptr) return;
	
	_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);

	animInstance->MovementSpeed = _acceleratedMovementSpeed;

	if (_inputVector == FVector::ZeroVector) return;
	
	const FRotator& cameraRotator = FRotator(0.f, _directionYaw, 0.f);
	
	_acceleratedCharacterDirection = cameraRotator.Vector();
		
	_character->SetActorRelativeRotation(_acceleratedCharacterDirection);
}





