#include "Sequence/SequenceStep.h"

#include "Misc/Logging.h"

void USequenceStep::ExecuteStep()
{
	PI_LOGV_UOBJECT(Error, TEXT("ExecuteStep not implemented"))
}

void USequenceStep::Finish()
{
	FinishedDelegate.ExecuteIfBound(this);
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
			FTimerDelegate::CreateLambda([this] { ExecuteStep(); }),
			_delay, false);

		return;
	}

	ExecuteStep();
}
