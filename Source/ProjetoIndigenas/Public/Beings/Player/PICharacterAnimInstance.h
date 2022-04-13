#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimationState.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "PICharacterAnimInstance.generated.h"

DECLARE_DELEGATE(FPICharacterAnimationEventDelegate)

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UPIAnimInstanceBase
{
	GENERATED_BODY()

public:
	FPICharacterAnimationEventDelegate ClimbingStartedDelegate;
	FPICharacterAnimationEventDelegate ClimbingEndedDelegate;
	FPICharacterAnimationEventDelegate BeginSynchronizingClimbingDelegate;
	FPICharacterAnimationEventDelegate EndSynchronizingClimbingDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPICharacterAnimationState State;

	UFUNCTION(BlueprintCallable)
	void OnClimbingStarted() { ClimbingStartedDelegate.ExecuteIfBound(); }

	UFUNCTION(BlueprintCallable)
	void OnClimbingEnded() { ClimbingEndedDelegate.ExecuteIfBound(); }
	
	UFUNCTION(BlueprintCallable)
	void OnBeginSynchronizingClimbing() { BeginSynchronizingClimbingDelegate.ExecuteIfBound(); }
	
	UFUNCTION(BlueprintCallable)
	void OnEndSynchronizingClimbing() { EndSynchronizingClimbingDelegate.ExecuteIfBound(); }
};
