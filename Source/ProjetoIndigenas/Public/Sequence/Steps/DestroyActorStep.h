#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "DestroyActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UDestroyActorStep : public USequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Instanced, meta = (ExposeOnSpawn))
	UActorProviderBase* _actorProvider;

	virtual void ExecuteStep() override;
};
