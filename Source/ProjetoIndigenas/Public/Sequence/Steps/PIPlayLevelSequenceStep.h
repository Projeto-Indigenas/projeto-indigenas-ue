#pragma once

#include "CoreMinimal.h"
#include "Sequence/Steps/Base/PISequenceStepBase.h"
#include "PIPlayLevelSequenceStep.generated.h"

class ALevelSequenceActor;
class ULevelSequence;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIPlayLevelSequenceStep : public UPISequenceStepBase
{
	GENERATED_BODY()

	UFUNCTION()
	void PlaybackFinished();
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<ALevelSequenceActor> _sequenceActor;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TObjectPtr<ULevelSequence> _levelSequenceToPlay;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _setViewTarget;

public:
	virtual void ExecuteStep() override;
};
