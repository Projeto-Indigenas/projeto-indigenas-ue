#pragma once

#include "CoreMinimal.h"
#include "Sequence/Steps/Base/PISequenceStepBase.h"
#include "Sequence/PISequenceStepExecutor.h"
#include "PIPlayLevelSequenceStep.generated.h"

class ALevelSequenceActor;
class ULevelSequence;
class FPISkipCutsceneAction;
class UPIDialog;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIPlayLevelSequenceStep : public UPISequenceStepBase, public IPISequenceStepExecutor
{
	GENERATED_BODY()

	bool skipped;

	TSharedPtr<FPISkipCutsceneAction> _skipCutsceneAction;
	
	UFUNCTION()
	void PlaybackFinished();
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<ALevelSequenceActor> _sequenceActor;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TObjectPtr<ULevelSequence> _levelSequenceToPlay;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TObjectPtr<UPIDialog> _dialog;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _setViewTarget;

public:
	virtual void ExecuteStep() override;

	void Skip();
};
