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
	step->SequenceStepFinishedDelegate.Unbind();

	ExecuteNextStep();
}

void FSequence::BeginPlay(UGameInstance* gameInstance)
{
	for (USequenceStep* step : _steps)
	{
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
	step->SequenceStepFinishedDelegate.BindRaw(this, &FSequence::StepFinished);
	step->Execute();
}
