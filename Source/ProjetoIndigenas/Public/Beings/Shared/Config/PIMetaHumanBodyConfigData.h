#pragma once

#include <GroomAsset.h>

#include "CoreMinimal.h"
#include "PIMetaHumanBodyConfigData.generated.h"

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FPIMetaHumanGroomConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSoftObjectPtr<UMaterialInstance>> HairMaterials;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<UGroomAsset> GroomAsset;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<UGroomBindingAsset> GroomBindingAsset;
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIMetaHumanBodyConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> CharacterBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> CharacterFace;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FPIMetaHumanGroomConfig HairConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FPIMetaHumanGroomConfig FuzzConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FPIMetaHumanGroomConfig EyelashesConfig;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FPIMetaHumanGroomConfig EyebrowsConfig;
};
