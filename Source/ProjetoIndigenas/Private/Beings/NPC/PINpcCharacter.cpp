#include "Beings/NPC/PINpcCharacter.h"

#include "Beings/Shared/States/PIMovementState.h"

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

void APINpcCharacter::SetInputX(float x)
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->HorizontalInputDelegate.ExecuteIfBound(x);
}

void APINpcCharacter::SetInputY(float y)
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->VerticalInputDelegate.ExecuteIfBound(y);
}
