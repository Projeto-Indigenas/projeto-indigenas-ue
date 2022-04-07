#pragma once

#include "CoreMinimal.h"
#include "Base/PISequenceStepTargetActorBase.h"
#include "PIDestroyActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIDestroyActorStep : public UPISequenceStepTargetActorBase
{
	GENERATED_BODY()

protected:
	virtual void ExecuteStep() override;
};
