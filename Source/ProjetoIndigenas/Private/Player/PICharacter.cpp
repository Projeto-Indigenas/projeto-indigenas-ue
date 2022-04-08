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
	if (!_animInstance.IsValid() || !_animInstance->IsClimbing)
	{
		Super::Tick(DeltaSeconds);

		return;
	}
	
	AActor::Tick(DeltaSeconds);
	
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
}

void APICharacter::StartClimbing()
{
	if (!_canStartClimbingTree) return;
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Flying;
	_animInstance->State = EPICharacterAnimationState::Climbing;
}

void APICharacter::StopClimbing()
{
	if (!_animInstance.IsValid()) return;

	GetCharacterMovement()->MovementMode = MOVE_Walking;
	_animInstance->State = EPICharacterAnimationState::Movement;
}
