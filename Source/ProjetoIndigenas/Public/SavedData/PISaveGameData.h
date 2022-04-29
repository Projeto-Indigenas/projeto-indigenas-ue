#pragma once

#include <GameFramework/SaveGame.h>

#include "CoreMinimal.h"
#include "PISaveGameData.generated.h"

USTRUCT(BlueprintType)
struct FPIPlayerCharacterSavedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName CharacterId;
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FPIPlayerCharacterSavedData PlayerCharacterSavedData;
};
