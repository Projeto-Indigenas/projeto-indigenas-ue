#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "ToggleActorVisibilityStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UToggleActorVisibilityStep : public USequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> _targetActor;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _visible;
	
	virtual void ExecuteStep() override;
};
