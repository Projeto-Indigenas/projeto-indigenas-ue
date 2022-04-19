#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.h"
#include "PlayerActorProvider.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UPlayerActorProvider : public UActorProviderBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	int PlayerIndex = 0;
	
public:
	virtual AActor* GetActor() const override;
};
