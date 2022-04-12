#include "Player/States/PIClimbingState.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Player/PIAnimInstanceBase.h"

void FPIClimbingState::UpdateMovementSpeed()
{
	if (_animInstance.IsValid() && _animInstance->IsClimbing) 
	{
		_acceleratedMovementSpeed = _inputVector.X;
	}
}

FPIClimbingState::FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData):
	FPIStateBaseWithData(character, stateData)
{
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;

	_acceleratedCapsuleRadius = stateData.CapsuleRadius;
	_acceleratedCapsuleRadius.Acceleration = stateData.CapsuleRadiusAcceleration;
}

void FPIClimbingState::Tick(float DeltaSeconds)
{
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);
	
	if (_capsuleComponent.IsValid())
	{
		_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	}

	if (_animInstance.IsValid())
	{
		_animInstance->MovementSpeed = _acceleratedMovementSpeed;

		if (_animInstance->IsClimbing)
		{
			_character->GetCharacterMovement()->Velocity = FVector::ZeroVector;
		}
	}
}
