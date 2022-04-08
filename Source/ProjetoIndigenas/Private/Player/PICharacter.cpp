#include "Player/PICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PICharacterAnimInstance.h"

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = GetAnimInstance<UPICharacterAnimInstance>();
}

void APICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (_animInstance.IsValid() && _animInstance->IsClimbing)
	{
		GetCharacterMovement()->Velocity = FVector::ZeroVector;
	}
}

void APICharacter::StartClimbing()
{
	if (!_canStartClimbingTree) return;
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Flying;
	
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Climbing;
	_animInstance->State = state;

	SetCapsuleRadius(_capsuleRadiusForState.Find(state));
	SetMovementAcceleration(_movementAccelerationForState.Find(state));
}

void APICharacter::StopClimbing()
{
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Walking;
	const EPICharacterAnimationState& state = EPICharacterAnimationState::Movement;
	_animInstance->State = state;
	
	SetCapsuleRadius(_capsuleRadiusForState.Find(state));
	SetMovementAcceleration(_movementAccelerationForState.Find(state));
}
