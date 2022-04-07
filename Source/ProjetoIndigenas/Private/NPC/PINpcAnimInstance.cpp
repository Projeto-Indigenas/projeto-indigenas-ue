#include "NPC/PINpcAnimInstance.h"

void UPINpcAnimInstance::AnimationCompleted()
{
	AnimationCompletedDelegate.ExecuteIfBound();
}
