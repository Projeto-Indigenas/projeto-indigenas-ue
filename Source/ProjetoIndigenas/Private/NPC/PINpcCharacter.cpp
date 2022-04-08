#include "NPC/PINpcCharacter.h"

#include "NPC/PINpcAnimInstance.h"

void APINpcCharacter::StartClimbing()
{
	if (!_canStartClimbingTree) return;

	UPINpcAnimInstance* animInstance = GetAnimInstance<UPINpcAnimInstance>();
	if (animInstance == nullptr) return;
	animInstance->State = EPINpcAnimationState::Climbing;
}
