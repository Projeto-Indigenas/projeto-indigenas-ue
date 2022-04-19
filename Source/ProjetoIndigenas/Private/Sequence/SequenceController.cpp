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
	SequenceCompletedDelegate.ExecuteIfBound();

	UE_LOG(LogTemp, Log, TEXT("Sequence Completed"))
}

void ASequenceController::BeginPlay()
{
	Super::BeginPlay();

	_subsystem = GetWorld()->GetSubsystem<USequenceSubsystem>();
	_subsystem->RegisterOwner(this);

	SequenceCompletedDelegate.BindUObject(this, &ASequenceController::SequenceCompleted);

	UGameInstance* gameInstance = GetGameInstance();
	for (USequenceStep* step : _steps)
	{
		if (step == nullptr) continue;
		
		step->BeginPlay(gameInstance);
	}

	if (!_startAutomatically) return;

	StartSequence();
}

void ASequenceController::Destroyed()
{
	Super::Destroyed();

	if (!_subsystem.IsValid()) return;
	_subsystem->UnregisterOwner(this);
}

void ASequenceController::ExecuteNextStep()
{
	if (!NextIndex())
	{
		SequenceCompletedDelegate.ExecuteIfBound();

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
