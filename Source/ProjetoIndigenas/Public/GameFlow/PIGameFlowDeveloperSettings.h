#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.h"
#include "PIGameFlowDeveloperSettings.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<UPIGameFlowData> GameFlowData;
};
