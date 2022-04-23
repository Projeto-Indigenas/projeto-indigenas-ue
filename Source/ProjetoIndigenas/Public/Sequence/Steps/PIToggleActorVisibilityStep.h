#pragma once

#include "CoreMinimal.h"
#include "Base/PISequenceStepTargetActorBase.h"
#include "PIToggleActorVisibilityStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIToggleActorVisibilityStep : public UPISequenceStepTargetActorBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _visible;
	
	virtual void ExecuteStep() override;
};
