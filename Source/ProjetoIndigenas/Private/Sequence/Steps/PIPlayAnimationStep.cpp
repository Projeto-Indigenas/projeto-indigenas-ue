#include "Sequence/Steps/PIPlayAnimationStep.h"

#include "GameFramework/Character.h"
#include "Beings/NPC/PINpcAnimInstance.h"
#include "Misc/Logging.h"

bool UPIPlayAnimationStep::GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const
{
	const USkeletalMeshComponent* meshComponent = _targetCharacter->GetMesh();
	if (meshComponent == nullptr) return false;
	UAnimInstance* animInstance = meshComponent->GetAnimInstance();
	if (animInstance == nullptr) return false;
	outAnimInstance = Cast<UPINpcAnimInstance>(animInstance);
	return outAnimInstance != nullptr;
}

void UPIPlayAnimationStep::ExecuteStep()
{
	Super::ExecuteStep();

	_targetCharacter = GetTargetActor<ACharacter>();
	
	if (!_targetCharacter.IsValid())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Target actor is invalid"))

		Finish();
		
		return;
	}

	UPINpcAnimInstance* animInstance;
	
	if (!GetAnimInstance(animInstance))
	{
		Finish();

		return;
	}

	animInstance->State = _animationStateToPlay;
	
	if (_waitForAnimationCompletedEvent)
	{
		animInstance->AnimationCompletedDelegate.BindDynamic(this, &UPIPlayAnimationStep::AnimationCompleted);

		return;
	}
	
	Finish();
}

void UPIPlayAnimationStep::AnimationCompleted()
{
	UPINpcAnimInstance* animInstance;

	if (GetAnimInstance(animInstance))
	{
		animInstance->AnimationCompletedDelegate.Unbind();
	}
	
	Finish();
}
