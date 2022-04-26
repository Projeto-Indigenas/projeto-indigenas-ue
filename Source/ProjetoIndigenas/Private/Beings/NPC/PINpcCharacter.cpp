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
}

void APINpcCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetCurrentState(_movementState);
}

void APINpcCharacter::UnPossessed()
{
	Super::UnPossessed();

	SetCurrentState(nullptr);
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

void APINpcCharacter::SetDirectionYaw(float yaw)
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->DirectionYawDelegate.ExecuteIfBound(yaw);
}
