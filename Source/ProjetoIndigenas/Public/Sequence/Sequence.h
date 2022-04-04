#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.h"
#include "Sequence.generated.h"

DECLARE_DELEGATE(FSequenceCompletedDelegate)

UCLASS()
class PROJETOINDIGENAS_API USequence : public UDataAsset
{
	GENERATED_BODY()

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
