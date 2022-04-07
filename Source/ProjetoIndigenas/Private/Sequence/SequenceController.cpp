#include "Sequence/SequenceController.h"

void ASequenceController::DelayToStartTimerAction()
{
	_sequence.ExecuteNextStep();
}

void ASequenceController::SequenceCompleted() const
{
	SequenceCompletedDelegate.ExecuteIfBound();

	UE_LOG(LogTemp, Log, TEXT("Sequence Completed"))
}

void ASequenceController::BeginPlay()
{
	Super::BeginPlay();

	_sequence.SequenceCompletedDelegate.BindUObject(this, &ASequenceController::SequenceCompleted);
	_sequence.BeginPlay(GetGameInstance());

	if (!_startAutomatically) return;

	StartSequence();
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

	_sequence.ExecuteNextStep();
}
