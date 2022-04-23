#pragma once

#include "CoreMinimal.h"
#include "Sequence/PISequenceStep.h"
#include "PIToggleActorVisibilityStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIToggleActorVisibilityStep : public UPISequenceStep
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<AActor> _targetActor;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _visible;
	
	virtual void ExecuteStep() override;
};
