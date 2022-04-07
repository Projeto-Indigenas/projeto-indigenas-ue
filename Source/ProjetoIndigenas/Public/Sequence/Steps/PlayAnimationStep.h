#pragma once

#include "CoreMinimal.h"
#include "NPC/NpcAnimationState.h"
#include "NPC/PINpcAnimInstance.h"
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
	ENpcAnimationState _animationStateToPlay;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _waitForAnimationCompletedEvent;

	virtual void ExecuteStep(const FSequenceQuery* sequenceQuery) override;

	UFUNCTION()
	void AnimationCompleted();
};
