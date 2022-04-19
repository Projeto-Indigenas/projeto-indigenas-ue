#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.h"
#include "WorldActorProvider.generated.h"

struct FSequenceQuery;

UCLASS()
class PROJETOINDIGENAS_API UWorldActorProvider : public UActorProviderBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<AActor> _worldActor;
	
	virtual AActor* GetActor() const override;
};
