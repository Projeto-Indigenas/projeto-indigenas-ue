#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.h"
#include "Sequence.generated.h"

DECLARE_DELEGATE(FSequenceCompletedDelegate)

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FSequenceQuery
{
	GENERATED_BODY()
	
	virtual ~FSequenceQuery() = default;
	virtual AActor* FindActor(const FName& name) const { return nullptr; }
};

USTRUCT(BlueprintType)
struct PROJETOINDIGENAS_API FSequence : public FSequenceQuery
{
	GENERATED_BODY()

private:
	TMap<FName, TWeakObjectPtr<AActor>> _spawnedActors;
	
	int _sequenceIndex = -1;

	bool NextIndex();
	void StepFinished(USequenceStep* step);
	void SpawnedActor(const FName& actorName, AActor* actor);

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _loopSteps = false;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Instanced)
	TArray<USequenceStep*> _steps;
	
public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;
	
	void BeginPlay(UGameInstance* gameInstance);
	void ExecuteNextStep();

	virtual AActor* FindActor(const FName& name) const override;
};
