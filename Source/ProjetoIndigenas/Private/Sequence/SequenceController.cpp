#include "Sequence/SequenceController.h"

bool ASequenceController::NextIndex()
{
	++_sequenceIndex;
	if (_sequenceIndex < _steps.Num()) return true;
	if (!_loopSteps) return false;
	_sequenceIndex = 0;
	return true;
}

void ASequenceController::StepFinished(USequenceStep* step)
{
	step->FinishedDelegate.Unbind();

	ExecuteNextStep();
}

void ASequenceController::DelayToStartTimerAction()
{
	ExecuteNextStep();
}

void ASequenceController::SequenceCompleted() const
{
	SequenceCompletedDelegate.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Sequence Completed"))
}

void ASequenceController::BeginPlay()
{
	Super::BeginPlay();

	if (!_startAutomatically) return;

	StartSequence();
}

void ASequenceController::ExecuteNextStep()
{
	if (!NextIndex())
	{
		SequenceCompleted();

		return;
	}

	USequenceStep* step = _steps[_sequenceIndex];
	if (step == nullptr) return;
	
	step->FinishedDelegate.BindUObject(this, &ASequenceController::StepFinished);
	
	step->Execute();
}

void ASequenceController::AddStep(USequenceStep* step)
{
	_steps.Add(step);
}

void ASequenceController::StartSequence()
{
	CreateSteps();
	
	UGameInstance* gameInstance = GetGameInstance();
	for (USequenceStep* step : _steps)
	{
		if (step == nullptr) continue;
		
		step->BeginPlay(gameInstance);
	}
	
	if (_delayToStart > 0.f)
	{
		FTimerHandle handle;
		GetGameInstance()->GetTimerManager().SetTimer(handle,
			FTimerDelegate::CreateUObject(this, &ASequenceController::DelayToStartTimerAction),
			_delayToStart, false);
		
		return;
	}

	ExecuteNextStep();
}

void ASequenceController::CreateSteps_Implementation()
{
	// to be overriden by blueprints
}
