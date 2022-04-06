#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "ToggleActorVisibilityStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UToggleActorVisibilityStep : public USequenceStep
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TObjectPtr<AActor> _targetActor;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _visible;
	
protected:
	virtual void ExecuteStep() override;
};
