#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PIAnimInstanceBase.generated.h"

DECLARE_DELEGATE(FPIAnimationEventDelegate)

UCLASS()
class PROJETOINDIGENAS_API UPIAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	FPIAnimationEventDelegate TurnStartedDelegate;
	FPIAnimationEventDelegate TurnEndedDelegate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementDirectionAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShouldDodge;

	UFUNCTION(BlueprintCallable)
	void OnTurnStarted() { TurnStartedDelegate.ExecuteIfBound(); }

	UFUNCTION(BlueprintCallable)
	void OnTurnEnded() { TurnEndedDelegate.ExecuteIfBound(); }
};
