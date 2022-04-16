#include "Beings/NPC/PINpcCharacter.h"

#include "Beings/Player/States/PIMovementState.h"

void APINpcCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateMovementState(
		_capsuleRadiusForState[EPINpcAnimationState::Movement],
		_movementAccelerationForState[EPINpcAnimationState::Movement]);

	CreateClimbingState(
		_capsuleRadiusForState[EPINpcAnimationState::Climbing],
		_movementAccelerationForState[EPINpcAnimationState::Climbing]);

	SetCurrentState(_movementState);
}
