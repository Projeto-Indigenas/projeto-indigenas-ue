#include "Sequence/Sequence.h"

bool FSequence::NextIndex()
{
	++_sequenceIndex;
	if (_sequenceIndex < _steps.Num()) return true;
	if (!_loopSteps) return false;
	_sequenceIndex = 0;
	return true;
}

void FSequence::StepFinished(USequenceStep* step)
{
	step->FinishedDelegate.Unbind();
	step->SpawnedActorDelegate.Unbind();

	ExecuteNextStep();
}

void FSequence::SpawnedActor(const FName& actorName, AActor* actor)
{
	_spawnedActors.Add(actorName, actor);
}

void FSequence::BeginPlay(UGameInstance* gameInstance)
{
	for (USequenceStep* step : _steps)
	{
		if (step == nullptr) continue;
		
		step->BeginPlay(gameInstance);
	}
}

void FSequence::ExecuteNextStep()
{
	if (!NextIndex())
	{
		SequenceCompletedDelegate.ExecuteIfBound();

		return;
	}

	USequenceStep* step = _steps[_sequenceIndex];
	if (step == nullptr) return;
	
	step->FinishedDelegate.BindRaw(this, &FSequence::StepFinished);
	step->SpawnedActorDelegate.BindRaw(this, &FSequence::SpawnedActor);
	
	step->Execute(*this);
}

AActor* FSequence::FindActor(const FName& name) const
{
	const TWeakObjectPtr<AActor>* weakActor = _spawnedActors.Find(name);
	if (weakActor == nullptr) return nullptr;
	return weakActor->Get();
}
