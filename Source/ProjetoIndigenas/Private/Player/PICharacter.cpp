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
	_characterStates.Add(EPICharacterAnimationState::Movement, MakeShared<FPIMovementState>(
		this, FPIMovementStateData(
			_capsuleRadiusForState[EPICharacterAnimationState::Movement],
			_capsuleRadiusAcceleration,
			_rotationAcceleration,
			_movementAccelerationForState[EPICharacterAnimationState::Movement]
			)));
	
	_characterStates.Add(EPICharacterAnimationState::Climbing, MakeShared<FPIClimbingState>(
		this, FPIClimbingStateData(
			_capsuleRadiusForState[EPICharacterAnimationState::Climbing],
			_capsuleRadiusAcceleration,
			_movementAccelerationForState[EPICharacterAnimationState::Climbing]
			)));

	SetCurrentState(_characterStates[EPICharacterAnimationState::Movement]);
}

void APICharacter::StartClimbing()
{
	if (_climbableTree == nullptr) return;
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Flying;
	
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Climbing;
	_animInstance->State = state;

	SetCurrentState(_characterStates[EPICharacterAnimationState::Climbing]);
}

void APICharacter::StopClimbing()
{
	if (_climbableTree == nullptr) return;
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Walking;
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Movement;
	_animInstance->State = state;
	
	SetCurrentState(_characterStates[EPICharacterAnimationState::Movement]);
}

void APICharacter::SetClimbableTree(APIClimbableTree* tree)
{
	// should not unset tree if we are climbing
	if (_animInstance->State == EPICharacterAnimationState::Climbing) return;
	
	_climbableTree = tree;
}
