#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowStateData.h"
#include "PIGameFlowTransitionController.generated.h"

DECLARE_DELEGATE(FPIGameFlowStateDelegate);

UCLASS()
class PROJETOINDIGENAS_API UPIGameFlowTransitionController : public UObject
{
	GENERATED_BODY()
	
	FDelegateHandle _openLevelHandle;
	
	UFUNCTION() void OnOpenLevelCompleted(UWorld* world);

public:
	FPIGameFlowStateDelegate OnTransitionCompleted;
	
	void Transition(
		const UWorld* world,
		const UPIGameFlowStateData* to);
};
