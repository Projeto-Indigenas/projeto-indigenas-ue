#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.h"
#include "Sequence.generated.h"

DECLARE_DELEGATE(FSequenceCompletedDelegate)

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FSequence
{
	GENERATED_BODY()

private:
	int _sequenceIndex = -1;

	bool NextIndex();
	void StepFinished(USequenceStep* step);

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _loopSteps;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Instanced)
	TArray<USequenceStep*> _steps;
	
public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;
	
	void BeginPlay(UGameInstance* gameInstance);
	void ExecuteNextStep();
};
