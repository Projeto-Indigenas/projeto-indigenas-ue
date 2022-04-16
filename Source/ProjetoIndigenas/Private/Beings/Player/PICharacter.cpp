﻿#include "Beings/Player/PICharacter.h"

#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Player/States/PIMovementState.h"
#include "Interactables/PIClimbableTree.h"

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateMovementState(
		_capsuleRadiusForState[EPICharacterAnimationState::Movement],
		_movementAccelerationForState[EPICharacterAnimationState::Movement]);
	
	CreateClimbingState(
		_capsuleRadiusForState[EPICharacterAnimationState::Climbing],
		_movementAccelerationForState[EPICharacterAnimationState::Climbing]);

	SetCurrentState(_movementState);
}

void APICharacter::StartClimbing(APIClimbableTree* tree)
{
	_climbingState->Tree = tree;
	SetCurrentState(_climbingState);
}

void APICharacter::StopClimbing(APIClimbableTree* tree)
{
	SetCurrentState(_movementState);
}
