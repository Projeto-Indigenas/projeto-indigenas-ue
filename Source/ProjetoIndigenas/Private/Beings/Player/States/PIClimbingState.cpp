#include "Beings/Player/States/PIClimbingState.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Beings/Shared/PIAnimInstanceBase.h"

void FPIClimbingState::SetInputY(float y)
{
	if (*_characterAnimState != EPICharacterAnimationState::Climbing) return;
	
	_inputVector.X = y;

	UpdateMovementSpeed();
}

void FPIClimbingState::UpdateMovementSpeed()
{
	if (*_characterAnimState != EPICharacterAnimationState::Climbing) return;
	
	_acceleratedMovementSpeed = _inputVector.X;
}

void FPIClimbingState::UpdateClimbingSynchronizedLocation(bool climbing)
{
	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	
	const APIClimbableTree* tree = Tree.Get();
	const APICharacterBase* character = _character.Get();
	
	const float& positionRadius = climbing ? tree->GetSynchronizingPositionRadius() : tree->GetStartPositionRadius();
	_acceleratedLocation.SetNow(character->GetActorLocation());
	_acceleratedLocation = tree->GetActorLocation() - _startDirection * positionRadius;
	
	const float& acceleration = climbing
		? _stateData.SynchronizationAcceleration
		: _stateData.MovementSpeedAcceleration;
	_acceleratedLocation.SetAcceleration(acceleration);
}

FORCEINLINE void FPIClimbingState::SynchronizeCharacterLocation(APICharacterBase* character) const
{
	FVector location = _acceleratedLocation;
	location.Z = character->GetActorLocation().Z;
	character->SetActorLocation(location);
}

void FPIClimbingState::ClimbingStarted()
{
	UpdateClimbingSynchronizedLocation(true);

	_currentState = EPIClimbingState::HangingOnTree;
}

void FPIClimbingState::ClimbingEnded()
{
	UpdateClimbingSynchronizedLocation(false);

	InvokeOnExitDelegate();

	_currentState = EPIClimbingState::None;
}

void FPIClimbingState::BeginSynchronizingClimbing()
{
	_synchronizeClimbing = true;

	UpdateClimbingSynchronizedLocation(true);
}

void FPIClimbingState::EndSynchronizingClimbing()
{
	_synchronizeClimbing = false;
}

FPIClimbingState::FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>(character, stateData),
	_currentState(EPIClimbingState::None),
	_synchronizeClimbing(false)
{
	_characterMovement = character->GetCharacterMovement();

	_acceleratedDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedLocation.SetAcceleration(stateData.MovementSpeedAcceleration);
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;

	_acceleratedCapsuleRadius.Acceleration = stateData.CapsuleRadiusAcceleration;

	_characterAnimState = &_animInstance->State;
}

void FPIClimbingState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPIClimbingState::SetInputY);

	_inputVector = FVector::ZeroVector;
	_currentState = EPIClimbingState::FloorToTree;
	
	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;

	const APIClimbableTree* tree = Tree.Get();
	const APICharacterBase* character = _character.Get();
	const UCapsuleComponent* capsuleComponent = _capsuleComponent.Get();
	UCharacterMovementComponent* characterMovement = _characterMovement.Get();
	UPICharacterAnimInstance* animInstance = _animInstance.Get();

	animInstance->ClimbingStartedDelegate.BindRaw(this, &FPIClimbingState::ClimbingStarted);
	animInstance->ClimbingEndedDelegate.BindRaw(this, &FPIClimbingState::ClimbingEnded);
	animInstance->BeginSynchronizingClimbingDelegate.BindRaw(this, &FPIClimbingState::BeginSynchronizingClimbing);
	animInstance->EndSynchronizingClimbingDelegate.BindRaw(this, &FPIClimbingState::EndSynchronizingClimbing);
	
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
	_startDirection = treeLocation - actorLocation;
	_startDirection.Normalize();
	_acceleratedDirection = _startDirection;

	UpdateClimbingSynchronizedLocation(false);
}

void FPIClimbingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPIClimbingStateBase::Exit(inputDelegates, onExitDelegate);
	
	inputDelegates.VerticalInputDelegate.Unbind();
	
	_inputVector = FVector::ZeroVector;

	if (!_characterMovement.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	UPICharacterAnimInstance* animInstance = _animInstance.Get();
	UCharacterMovementComponent* characterMovement = _characterMovement.Get();
	
	animInstance->ClimbingStartedDelegate.Unbind();
	animInstance->ClimbingEndedDelegate.Unbind();
	animInstance->BeginSynchronizingClimbingDelegate.Unbind();
	animInstance->EndSynchronizingClimbingDelegate.Unbind();

	characterMovement->MovementMode = MOVE_Walking;
	*_characterAnimState = EPICharacterAnimationState::Movement;

	_currentState = EPIClimbingState::TreeToFloor;
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
	
	animInstance->MovementSpeed = _acceleratedMovementSpeed;

	character->SetActorRotation(_acceleratedDirection);
	switch (_currentState)
	{
	case EPIClimbingState::FloorToTree:
		{
			const bool isOnTarget = _acceleratedLocation.IsOnTarget(1.f);
			if (isOnTarget && animInstance->State != EPICharacterAnimationState::Climbing)
			{
				animInstance->State = EPICharacterAnimationState::Climbing;
			}

			SynchronizeCharacterLocation(character);
			
			break;
		}
	case EPIClimbingState::HangingOnTree:
		{
			if (_synchronizeClimbing)
			{
				SynchronizeCharacterLocation(character);
			}
			
			break;
		}
	default: break;
	}
}
