#pragma once

#include "CoreMinimal.h"
#include "PIGameFlowStateBase.h"
#include "GameFlow/PIGameFlowSettings.h"
#include "PIGameFlowStateWorldTransition.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowStateWorldTransition : public UPIGameFlowStateBase
{
	GENERATED_BODY()

	void OnLevelLoaded(UWorld* world);
	void OnTransitionLevelLoaded(UWorld* world);
	void DequeueAndLoadStreamingLevel(const UWorld* world);
	void StreamingLevelLoaded();
	
	TQueue<TSoftObjectPtr<UWorld>> _streamingLevelsQueue;
	FDelegateHandle _persistentLevelHandle;
	TWeakObjectPtr<const UPIGameFlowSettings> _settings;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> _persistentLevel;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<UWorld>> _streamingLevels;

	virtual void Enter(FPIGameFlowStateTransitionDelegate completed) override;
	virtual void Exit(FPIGameFlowStateTransitionDelegate completed) override;

	virtual void PostLoad() override;
};
