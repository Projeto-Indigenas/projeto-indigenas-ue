#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PIAnimInstanceBase.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPIAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShouldDodge;
};
