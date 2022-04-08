#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimationState.h"
#include "PIAnimInstanceBase.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UPIAnimInstanceBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPICharacterAnimationState State;
};
