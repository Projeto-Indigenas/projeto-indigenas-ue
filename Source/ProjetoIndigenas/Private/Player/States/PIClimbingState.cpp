#include "Player/States/PIClimbingState.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Player/PIAnimInstanceBase.h"

void FPIClimbingState::SetInputY(float y)
{
	_inputVector.X = y;

	UpdateMovementSpeed();
}

void FPIClimbingState::UpdateMovementSpeed()
{
	if (_animInstance.IsValid() && _animInstance->IsClimbing) 
	{
		_acceleratedMovementSpeed = _inputVector.X;
	}
}

FPIClimbingState::FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>(character, stateData)
{
	_characterMovement = character->GetCharacterMovement();
	
	_acceleratedDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedLocation.SetAcceleration(stateData.MovementSpeedAcceleration);
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;
	
	_acceleratedCapsuleRadius.Acceleration = stateData.CapsuleRadiusAcceleration;
}

void FPIClimbingState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPIClimbingState::SetInputY);

	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;

	const APIClimbableTree* tree = Tree.Get();
	const APICharacterBase* character = _character.Get();
	const UCapsuleComponent* capsuleComponent = _capsuleComponent.Get();
	UCharacterMovementComponent* characterMovement = _characterMovement.Get();
	
	characterMovement->MovementMode = MOVE_Flying;
	
	FVector actorLocation = character->GetActorLocation();
	_acceleratedLocation.SetNow(actorLocation);
	FVector currentDirection = character->GetActorRotation().Vector();
	currentDirection.Normalize();
	_acceleratedDirection.SetNow(currentDirection);

	_acceleratedCapsuleRadius.SetNow(capsuleComponent->GetScaledCapsuleRadius());
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;

	FVector treeLocation = tree->GetActorLocation();
	actorLocation.Z = 0;
	treeLocation.Z = 0;
	FVector direction = treeLocation - actorLocation;
	direction.Normalize();

	const float& positionRadius = tree->GetStartPositionRadius();
	_acceleratedLocation = tree->GetActorLocation() - direction * positionRadius;
	_acceleratedDirection = direction;
}

void FPIClimbingState::Exit(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.Unbind();
	
	_inputVector = FVector::ZeroVector;

	if (!_characterMovement.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	UCharacterMovementComponent* characterMovement = _characterMovement.Get();
	UPICharacterAnimInstance* animInstance = _animInstance.Get();
	
	characterMovement->MovementMode = MOVE_Walking;
	animInstance->State = EPICharacterAnimationState::Movement;
}

void FPIClimbingState::Tick(float DeltaSeconds)
{
	_acceleratedLocation.Tick(DeltaSeconds);
	_acceleratedDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);

	if (!_character.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;
	
	APICharacterBase* character = _character.Get();
	UCharacterMovementComponent* characterMovement = _characterMovement.Get();
	UPICharacterAnimInstance* animInstance = _animInstance.Get();
	UCapsuleComponent* capsuleComponent = _capsuleComponent.Get();
	
	capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	characterMovement->Velocity = FVector::ZeroVector;

	character->SetActorRotation(_acceleratedDirection);
	if (!_acceleratedLocation.IsOnTarget(1.f))
	{
		FVector location = _acceleratedLocation;
		location.Z = character->GetActorLocation().Z;
		character->SetActorLocation(location);

		return;
	}

	if (animInstance->State != EPICharacterAnimationState::Climbing)
	{
		animInstance->State = EPICharacterAnimationState::Climbing;
	}

	animInstance->MovementSpeed = _acceleratedMovementSpeed;
}
