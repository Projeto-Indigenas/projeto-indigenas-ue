#include "Sequence/Sequence.h"

bool USequence::NextIndex()
{
	++_sequenceIndex;
	if (_sequenceIndex < _steps.Num()) return true;
	if (!_loopSteps) return false;
	_sequenceIndex = 0;
	return true;
}

void USequence::StepFinished(USequenceStep* step)
{
	step->SequenceStepFinishedDelegate.Unbind();

	ExecuteNextStep();
}

void USequence::BeginPlay()
{
	for (USequenceStep* step : _steps)
	{
		step->BeginPlay();
	}
}

void USequence::ExecuteNextStep()
{
	if (!NextIndex())
	{
		SequenceCompletedDelegate.ExecuteIfBound();

		return;
	}

	USequenceStep* step = _steps[_sequenceIndex];
	step->SequenceStepFinishedDelegate.BindUObject(this, &USequence::StepFinished);
	step->Execute();
}
