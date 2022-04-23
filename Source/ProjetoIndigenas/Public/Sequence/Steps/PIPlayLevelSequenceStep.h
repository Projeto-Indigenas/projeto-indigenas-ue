#pragma once

#include "CoreMinimal.h"
#include "Sequence/PISequenceStep.h"
#include "PIPlayLevelSequenceStep.generated.h"

class ALevelSequenceActor;
class ULevelSequence;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIPlayLevelSequenceStep : public UPISequenceStep
{
	GENERATED_BODY()

	UFUNCTION()
	void PlaybackFinished();
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<ALevelSequenceActor> _sequenceActor;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TObjectPtr<ULevelSequence> _levelSequenceToPlay;

public:
	virtual void ExecuteStep() override;
};
