#pragma once

#include "CoreMinimal.h"
#include "PIMetaHumanBodyConfigData.h"
#include "PICharacterConfigurationData.generated.h"

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FPICharacterConfiguration
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName CharacterId;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UPIMetaHumanBodyConfigData> ChildBodyConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UPIMetaHumanBodyConfigData> AdultBodyConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UPIMetaHumanBodyConfigData> ElderBodyConfig;
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPICharacterConfigurationData : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FPICharacterConfiguration> _playerConfigurations;

	UPROPERTY(EditDefaultsOnly)
	TArray<FPICharacterConfiguration> _npcConfigurations;
	
public:
	UPROPERTY(BlueprintReadOnly, SkipSerialization)
	TMap<FName, FPICharacterConfiguration> PlayerCharactersMap;

	UPROPERTY(BlueprintReadOnly, SkipSerialization)
	TMap<FName, FPICharacterConfiguration> NpcCharactersMap;

	virtual void Serialize(FArchive& Ar) override;
};
