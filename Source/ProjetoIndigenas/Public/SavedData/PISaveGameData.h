#pragma once

#include <GameFramework/SaveGame.h>

#include "CoreMinimal.h"
#include "PISaveGameData.generated.h"

USTRUCT(BlueprintType)
struct FPIPlayerCharacterSavedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CharacterId;
};

UCLASS()
class PROJETOINDIGENAS_API UPISaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FPIPlayerCharacterSavedData PlayerCharacterSavedData;
};
