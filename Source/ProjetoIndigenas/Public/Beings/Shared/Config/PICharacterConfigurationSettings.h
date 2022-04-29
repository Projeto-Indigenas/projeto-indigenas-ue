#pragma once

#include "CoreMinimal.h"
#include "PICharacterConfigurationData.h"
#include "PICharacterConfigurationSettings.generated.h"

UCLASS(Config=Game, DefaultConfig)
class PROJETOINDIGENAS_API UPICharacterConfigurationSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<UPICharacterConfigurationData> CharacterConfigurationData;

	UPICharacterConfigurationSettings()
	{
		CategoryName = TEXT("1 - Projeto Indígenas");
	}
};
