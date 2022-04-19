#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "ToggleActorVisibilityStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UToggleActorVisibilityStep : public USequenceStep
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<AActor> _targetActor;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _visible;
	
	virtual void ExecuteStep() override;
};
