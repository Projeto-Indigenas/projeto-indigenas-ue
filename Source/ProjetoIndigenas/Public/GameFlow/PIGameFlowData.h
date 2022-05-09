#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.generated.h"

class UPIGameFlowStateData;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, UPIGameFlowStateData*> States;
};
