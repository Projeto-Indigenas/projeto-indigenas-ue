#include "Sequence/SequenceStep.h"

void USequenceStep::ExecuteStep()
{
	UE_LOG(LogTemp, Error, TEXT("ExecuteStep not implemented"))
}

void USequenceStep::Finish()
{
	SequenceStepFinishedDelegate.ExecuteIfBound(this);	
}

void USequenceStep::BeginPlay(UGameInstance* gameInstance)
{
	_gameInstance = gameInstance;
}

void USequenceStep::Execute()
{
	if (_skipStep)
	{
		Finish();

		return;
	}

	if (_delay > 0.f)
	{
		FTimerHandle handle;
		_gameInstance->GetTimerManager().SetTimer(handle,
			FTimerDelegate::CreateUObject(this, &USequenceStep::ExecuteStep),
			_delay, false);

		return;
	}

	ExecuteStep();
}
