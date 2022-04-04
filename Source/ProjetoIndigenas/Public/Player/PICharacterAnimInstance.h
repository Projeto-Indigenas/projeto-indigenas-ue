#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationState.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShouldDodge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterAnimationState State;
};
