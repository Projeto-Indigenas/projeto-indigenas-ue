#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.h"
#include "PIGameFlowSettings.generated.h"

UCLASS(Config = Game, DefaultConfig)
class PROJETOINDIGENAS_API UPIGameFlowSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditDefaultsOnly)
	TSoftObjectPtr<UPIGameFlowData> GameFlowData;

	UPROPERTY(Config, EditDefaultsOnly)
	TSoftObjectPtr<UWorld> TransitionLevel;

	UPIGameFlowSettings()
	{
		CategoryName = TEXT("1 - Projeto Indígenas");
	}
};
