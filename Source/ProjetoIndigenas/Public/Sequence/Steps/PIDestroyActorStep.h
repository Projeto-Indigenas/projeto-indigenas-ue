#pragma once

#include "CoreMinimal.h"
#include "Sequence/PISequenceStep.h"
#include "PIDestroyActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIDestroyActorStep : public UPISequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<AActor> _targetActor;

	virtual void ExecuteStep() override;
};
