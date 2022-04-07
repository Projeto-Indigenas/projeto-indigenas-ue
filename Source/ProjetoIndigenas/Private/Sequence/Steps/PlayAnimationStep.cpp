#include "Sequence/Steps/PlayAnimationStep.h"

#include "GameFramework/Character.h"
#include "NPC/PINpcAnimInstance.h"

bool UPlayAnimationStep::GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const
{
	const USkeletalMeshComponent* meshComponent = _targetCharacter->GetMesh();
	if (meshComponent == nullptr) return false;
	UAnimInstance* animInstance = meshComponent->GetAnimInstance();
	if (animInstance == nullptr) return false;
	outAnimInstance = Cast<UPINpcAnimInstance>(animInstance);
	return outAnimInstance != nullptr;
}

void UPlayAnimationStep::ExecuteStep(const FSequenceQuery* sequenceQuery)
{
	_targetCharacter = _actorProvider->GetActor<ACharacter>(sequenceQuery);

	if (!_targetCharacter.IsValid()) return;

	UPINpcAnimInstance* animInstance;
	
	if (!GetAnimInstance(animInstance))
	{
		Finish();

		return;
	}

	if (_waitForAnimationCompletedEvent)
	{
		animInstance->AnimationCompletedDelegate.BindDynamic(this, &UPlayAnimationStep::AnimationCompleted);
	}
	animInstance->State = _animationStateToPlay;
	if (!_waitForAnimationCompletedEvent)
	{
		Finish();
	}
}

void UPlayAnimationStep::AnimationCompleted()
{
	UPINpcAnimInstance* animInstance;

	if (GetAnimInstance(animInstance))
	{
		animInstance->AnimationCompletedDelegate.Unbind();
	}
	
	Finish();
}
