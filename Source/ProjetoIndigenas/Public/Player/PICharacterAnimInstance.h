#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationState.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool ShouldDodge;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	ECharacterAnimationState State;
};
