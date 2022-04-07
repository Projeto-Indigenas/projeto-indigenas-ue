#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationState.h"
#include "PIAnimInstanceBase.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UPIAnimInstanceBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterAnimationState State;
};
