#pragma once

#include "CoreMinimal.h"
#include "Beings/NPC/PINpcAnimationState.h"
#include "Beings/NPC/PINpcAnimInstance.h"
#include "Sequence/SequenceStep.h"
#include "PlayAnimationStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPlayAnimationStep : public USequenceStep
{
	GENERATED_BODY()

	bool GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<ACharacter> _targetCharacter;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	EPINpcAnimationState _animationStateToPlay;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _waitForAnimationCompletedEvent;

	virtual void ExecuteStep() override;

	UFUNCTION()
	void AnimationCompleted();
};
