#pragma once

#include "CoreMinimal.h"
#include "PIPathData.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPIPathData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
    TArray<FVector> Nodes;
};
