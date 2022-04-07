#pragma once

#include "CoreMinimal.h"
#include "NpcAnimationState.h"
#include "Player/PIAnimInstanceBase.h"
#include "PINpcAnimInstance.generated.h"

DECLARE_DYNAMIC_DELEGATE(FAnimationEventDelegate);

UCLASS()
class PROJETOINDIGENAS_API UPINpcAnimInstance : public UPIAnimInstanceBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void AnimationCompleted();
	
public:
	FAnimationEventDelegate AnimationCompletedDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ENpcAnimationState State;
};
