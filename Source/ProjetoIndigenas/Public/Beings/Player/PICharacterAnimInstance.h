#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimationState.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UPIAnimInstanceBase
{
	GENERATED_BODY()

public:
	FPIAnimationEventDelegate ClimbingStartedDelegate;
	FPIAnimationEventDelegate ClimbingEndedDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPICharacterAnimationState State;

	UFUNCTION(BlueprintCallable)
	void OnClimbingStarted() { ClimbingStartedDelegate.ExecuteIfBound(); }

	UFUNCTION(BlueprintCallable)
	void OnClimbingEnded() { ClimbingEndedDelegate.ExecuteIfBound(); }
};
