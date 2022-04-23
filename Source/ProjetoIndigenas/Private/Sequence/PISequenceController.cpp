#include "Sequence/PISequenceController.h"

bool APISequenceController::NextIndex()
{
	++_sequenceIndex;
	if (_sequenceIndex < _steps.Num()) return true;
	if (!_loopSteps) return false;
	_sequenceIndex = 0;
	return true;
}

void APISequenceController::StepFinished(UPISequenceStep* step)
{
	step->FinishedDelegate.Unbind();

	ExecuteNextStep();
}

void APISequenceController::DelayToStartTimerAction()
{
	ExecuteNextStep();
}

void APISequenceController::SequenceCompleted() const
{
	SequenceCompletedDelegate.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Sequence Completed"))
}

void APISequenceController::BeginPlay()
{
	Super::BeginPlay();

	if (!_startAutomatically) return;

	StartSequence();
}

void APISequenceController::ExecuteNextStep()
{
	if (!NextIndex())
	{
		SequenceCompleted();

		return;
	}

	UPISequenceStep* step = _steps[_sequenceIndex];
	if (step == nullptr) return;
	
	step->FinishedDelegate.BindUObject(this, &APISequenceController::StepFinished);
	
	step->Execute();
}

void APISequenceController::AddStep(UPISequenceStep* step)
{
	_steps.Add(step);
}

void APISequenceController::StartSequence()
{
	CreateSteps();
	
	UGameInstance* gameInstance = GetGameInstance();
	for (UPISequenceStep* step : _steps)
	{
		if (step == nullptr) continue;
		
		step->BeginPlay(gameInstance);
	}
	
	if (_delayToStart > 0.f)
	{
		FTimerHandle handle;
		GetGameInstance()->GetTimerManager().SetTimer(handle,
			FTimerDelegate::CreateUObject(this, &APISequenceController::DelayToStartTimerAction),
			_delayToStart, false);
		
		return;
	}

	ExecuteNextStep();
}

void APISequenceController::CreateSteps_Implementation()
{
	// to be overriden by blueprints
}
