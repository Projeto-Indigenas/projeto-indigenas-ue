#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowData.h"
#include "PIGameFlowSettings.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UPIGameFlowData> GameFlowData;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> TransitionLevel;

	UPIGameFlowSettings()
	{
		CategoryName = TEXT("Projeto Indígenas");
		SectionName = TEXT("Game Flow Settings");
	}
};
