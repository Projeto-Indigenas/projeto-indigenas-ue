#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.generated.h"

class UPIGameFlowStateBase;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FName, TObjectPtr<UPIGameFlowStateBase>> _gameFlowStateMap;
};
