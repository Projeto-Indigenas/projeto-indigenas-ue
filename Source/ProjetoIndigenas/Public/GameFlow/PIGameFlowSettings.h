#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.h"
#include "PIGameFlowSettings.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<UPIGameFlowData> GameFlowData;
};
