#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPICharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float MovementSpeed;
};
