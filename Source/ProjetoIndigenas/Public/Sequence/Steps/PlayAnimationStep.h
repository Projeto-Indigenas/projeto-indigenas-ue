#pragma once

#include "CoreMinimal.h"
#include "Beings/NPC/PINpcAnimationState.h"
#include "Beings/NPC/PINpcAnimInstance.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "PlayAnimationStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPlayAnimationStep : public USequenceStep
{
	GENERATED_BODY()

	TWeakObjectPtr<ACharacter> _targetCharacter;

	bool GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Instanced)
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	EPINpcAnimationState _animationStateToPlay;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _waitForAnimationCompletedEvent;

	virtual void ExecuteStep(const FSequenceQuery* sequenceQuery) override;

	UFUNCTION()
	void AnimationCompleted();
};
