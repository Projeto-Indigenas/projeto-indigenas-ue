#pragma once

#include "CoreMinimal.h"
#include "GameFlow/PIGameFlowSettings.h"
#include "PIGameFlowStateData.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowStateData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> PersistentLevel;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> StreamingLevels;
};
