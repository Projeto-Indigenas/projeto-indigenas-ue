#include "Beings/Player/PICharacter.h"

#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Player/States/PIMovementState.h"

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = GetAnimInstance<UPICharacterAnimInstance>();
}

void APICharacter::InitializeFromController()
{
	_movementState = MakeShared<FPIMovementState>(this,
		FPIMovementStateData(
			_capsuleRadiusForState[EPICharacterAnimationState::Movement],
			_capsuleRadiusAcceleration,
			_rotationAcceleration,
			_movementAccelerationForState[EPICharacterAnimationState::Movement]
		));
	
	_climbingState = MakeShared<FPIClimbingState>(this,
		FPIClimbingStateData(
			_capsuleRadiusForState[EPICharacterAnimationState::Climbing],
			_capsuleRadiusAcceleration,
			_movementAccelerationForState[EPICharacterAnimationState::Climbing],
			_rotationAcceleration
		));

	SetCurrentState(_movementState);
}

void APICharacter::StartClimbing(APIClimbableTree* tree)
{
	_climbingState->Tree = tree;
	SetCurrentState(_climbingState);
}

void APICharacter::StopClimbing(APIClimbableTree* tree)
{
	_climbingState->Tree = nullptr;
	SetCurrentState(_movementState);
}
