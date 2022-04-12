#include "Player/PICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PICharacterAnimInstance.h"
#include "Player/States/PIClimbingState.h"
#include "Player/States/PIMovementState.h"

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
			_movementAccelerationForState[EPICharacterAnimationState::Climbing]
		));

	SetCurrentState(_movementState);
}

void APICharacter::StartClimbing(APIClimbableTree* tree)
{
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Flying;
	
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Climbing;
	_animInstance->State = state;

	_climbingState->Tree = tree;
	SetCurrentState(_climbingState);
}

void APICharacter::StopClimbing(APIClimbableTree* tree)
{
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Walking;
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Movement;
	_animInstance->State = state;

	_climbingState->Tree = nullptr;
	SetCurrentState(_movementState);
}
