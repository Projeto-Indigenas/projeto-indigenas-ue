#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowStateBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FPIGameFlowStateTransitionDelegate);

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowStateBase : public UDataAsset
{
    GENERATED_BODY()

protected:
	FPIGameFlowStateTransitionDelegate _completedDelegate;

	void EnterTransitionCompleted();
	void ExitTransitionCompleted();

public:
    virtual void Enter(FPIGameFlowStateTransitionDelegate completed);
	virtual void Exit(FPIGameFlowStateTransitionDelegate completed);
};
