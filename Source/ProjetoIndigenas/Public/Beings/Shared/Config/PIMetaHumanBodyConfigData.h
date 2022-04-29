#pragma once

#include "CoreMinimal.h"
#include "PIMetaHumanBodyConfigData.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIMetaHumanBodyConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> CharacterBody;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSoftObjectPtr<USkeletalMesh> CharacterFace;
};
