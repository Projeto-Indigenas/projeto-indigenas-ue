#pragma once

#include "CoreMinimal.h"
#include "Beings/NPC/PINpcAnimationState.h"
#include "Beings/NPC/PINpcAnimInstance.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "PlayAnimationStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPlayAnimationStep : public USequenceStep
{
	GENERATED_BODY()

	TWeakObjectPtr<ACharacter> _targetCharacter;

	bool GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Instanced, meta = (ExposeOnSpawn))
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	EPINpcAnimationState _animationStateToPlay;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _waitForAnimationCompletedEvent;

	virtual void ExecuteStep() override;

	UFUNCTION()
	void AnimationCompleted();
};
