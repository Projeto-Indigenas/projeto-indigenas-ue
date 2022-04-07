#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.h"
#include "Sequence/Sequence.h"
#include "NamedActorProvider.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UNamedActorProvider : public UActorProviderBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FName ActorName;
	
	virtual AActor* GetActor(const FSequenceQuery* sequenceQuery) const override;
};
