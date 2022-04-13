#include "Beings/Player/States/PIClimbingState.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Interactables/PIClimbableTree.h"

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

void FPIClimbingState::UpdateTargetLocation()
{
	if (!Tree.IsValid()) return;
	const float& positionRadius = Tree->GetPositionRadiusMap()[_currentState];
	_acceleratedLocation = Tree->GetActorLocation() - _startDirection * positionRadius;
}

void FPIClimbingState::SynchronizeCharacterLocation() const
{
	if (!_character.IsValid()) return;
	
	FVector location = _acceleratedLocation;
	location.Z = _character->GetActorLocation().Z;
	_character->SetActorLocation(location);
}

void FPIClimbingState::ClimbingStarted()
{
	_currentState = EPIClimbingState::HangingOnTreeIdle;
	_acceleratedLocation.SetCurrent(_character->GetActorLocation());
	UpdateTargetLocation();
}

void FPIClimbingState::ClimbingEnded() const
{
	InvokeOnExitDelegate();
	
	if (!_animInstance.IsValid()) return;
	_animInstance->ClimbingStartedDelegate.Unbind();
	_animInstance->ClimbingEndedDelegate.Unbind();

	if (!_characterMovement.IsValid()) return;
	_characterMovement->MovementMode = MOVE_Walking;
}

FPIClimbingState::FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>(character, stateData),
	_currentState(EPIClimbingState::None)
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
	_currentState = EPIClimbingState::StartClimbing;
	
	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	if (!_animInstance.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;

	_animInstance->ClimbingStartedDelegate.BindRaw(this, &FPIClimbingState::ClimbingStarted);
	_animInstance->ClimbingEndedDelegate.BindRaw(this, &FPIClimbingState::ClimbingEnded);
	
	_characterMovement->MovementMode = MOVE_Flying;
	
	_acceleratedCapsuleRadius.SetCurrent(_capsuleComponent->GetScaledCapsuleRadius());
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;

	FVector actorLocation = _character->GetActorLocation();
	FVector treeLocation = Tree->GetActorLocation();
	actorLocation.Z = 0;
	treeLocation.Z = 0;
	_startDirection = treeLocation - actorLocation;
	_startDirection.Normalize();

	FVector currentDirection = _character->GetActorRotation().Vector();
	currentDirection.Normalize();
	_acceleratedDirection.SetCurrent(currentDirection);
	_acceleratedDirection = _startDirection;

	_acceleratedLocation.SetCurrent(_character->GetActorLocation());
	UpdateTargetLocation();
}

void FPIClimbingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPIClimbingStateBase::Exit(inputDelegates, onExitDelegate);
	
	inputDelegates.VerticalInputDelegate.Unbind();
	
	_inputVector = FVector::ZeroVector;
	_currentState = EPIClimbingState::EndClimbing;
	*_characterAnimState = EPICharacterAnimationState::Default;
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
	
	_characterMovement->Velocity = FVector::ZeroVector;
	_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	_animInstance->MovementSpeed = _acceleratedMovementSpeed;
	_character->SetActorRotation(_acceleratedDirection);

	switch (_currentState)
	{
	case EPIClimbingState::StartClimbing:
		{
			if (*_characterAnimState == EPICharacterAnimationState::Climbing) return;
			
			if (_acceleratedLocation.IsOnTarget(1.f))
			{
				*_characterAnimState = EPICharacterAnimationState::Climbing;

				return;
			}

			SynchronizeCharacterLocation();
			
			break;
		}
	case EPIClimbingState::HangingOnTreeIdle:
	case EPIClimbingState::HangingOnTreeMoving:
		{
			if (_inputVector.IsNearlyZero())
			{
				if (_currentState != EPIClimbingState::HangingOnTreeIdle)
				{
					_currentState = EPIClimbingState::HangingOnTreeIdle;
					return;
				}
			}
			else
			{
				if (_currentState != EPIClimbingState::HangingOnTreeMoving)
				{
					_currentState = EPIClimbingState::HangingOnTreeMoving;
					return;
				}
			}

			UpdateTargetLocation();
			SynchronizeCharacterLocation();
			
			break;
		}
	default: break;
	}
}
