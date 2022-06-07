#pragma once

#include "CoreMinimal.h"
#include "PIDialog.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPIDialog : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<FString> DialogLines;
};
