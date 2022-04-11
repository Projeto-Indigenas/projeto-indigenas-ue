#pragma once

#include "CoreMinimal.h"
#include "EditorOnly/PathEditor/PIPathEditorBase.h"
#include "PIPathData.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPIPathData : public UDataAsset, public IPIPathEditorDataProvider
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
    TArray<FVector> Nodes;

    FORCEINLINE virtual TArray<FVector>& GetNodes() override { return Nodes; }
};
