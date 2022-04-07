#include "Sequence/SequenceStep.h"

#include "Sequence/Sequence.h"

void USequenceStep::ExecuteStep(const FSequenceQuery* sequenceQuery)
{
	UE_LOG(LogTemp, Error, TEXT("ExecuteStep not implemented"))
}

void USequenceStep::Finish()
{
	FinishedDelegate.ExecuteIfBound(this);
}

void USequenceStep::BeginPlay(UGameInstance* gameInstance)
{
	_gameInstance = gameInstance;
}

void USequenceStep::Execute(const FSequenceQuery* sequenceQuery)
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
			FTimerDelegate::CreateLambda([this, sequenceQuery] { ExecuteStep(sequenceQuery); }),
			_delay, false);

		return;
	}

	ExecuteStep(sequenceQuery);
}
