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

	TArray<TSoftObjectPtr<UWorld>> _levelsToLoad;
	TArray<TObjectPtr<ULevelStreaming>> _levelsToUnload;
	
	UFUNCTION() void OnOpenLevelCompleted(UWorld* world);
	UFUNCTION() void LoadStreamLevel();
	UFUNCTION() void UnloadStreamLevel();

public:
	FPIGameFlowStateDelegate OnTransitionCompleted;
	
	void Transition(
		const UWorld* world,
		const UPIGameFlowStateData* to,
		const TSoftObjectPtr<UWorld>& sharedLevel);
};