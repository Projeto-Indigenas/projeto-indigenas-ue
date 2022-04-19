#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "DestroyActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UDestroyActorStep : public USequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<AActor> _targetActor;

	virtual void ExecuteStep() override;
};
