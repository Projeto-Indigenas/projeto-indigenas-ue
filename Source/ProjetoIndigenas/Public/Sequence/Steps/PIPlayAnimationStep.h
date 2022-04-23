#pragma once

#include "CoreMinimal.h"
#include "Base/PISequenceStepTargetActorBase.h"
#include "Beings/NPC/PINpcAnimationState.h"
#include "Beings/NPC/PINpcAnimInstance.h"
#include "PIPlayAnimationStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIPlayAnimationStep : public UPISequenceStepTargetActorBase
{
	GENERATED_BODY()

	TWeakObjectPtr<ACharacter> _targetCharacter;
	
	bool GetAnimInstance(UPINpcAnimInstance*& outAnimInstance) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	EPINpcAnimationState _animationStateToPlay;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _waitForAnimationCompletedEvent;

	virtual void ExecuteStep() override;

	UFUNCTION()
	void AnimationCompleted();

public:
	virtual void BeginPlay(UGameInstance* gameInstance) override;
};
