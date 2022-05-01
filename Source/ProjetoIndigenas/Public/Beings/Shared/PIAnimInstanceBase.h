#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PIAnimInstanceBase.generated.h"

DECLARE_DELEGATE(FPIAnimationEventDelegate)

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FPISwimAnimState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsAtSurface;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector2D SwimDirection;
};

UCLASS(BlueprintType)
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPISwimAnimState SwimAnimState;

	UFUNCTION(BlueprintCallable)
	void OnTurnStarted() { TurnStartedDelegate.ExecuteIfBound(); }

	UFUNCTION(BlueprintCallable)
	void OnTurnEnded() { TurnEndedDelegate.ExecuteIfBound(); }
};
