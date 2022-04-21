#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.generated.h"

class UPIGameFlowStateBase;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TMap<FName, TObjectPtr<UPIGameFlowStateBase>> _gameFlowStateMap;
};
