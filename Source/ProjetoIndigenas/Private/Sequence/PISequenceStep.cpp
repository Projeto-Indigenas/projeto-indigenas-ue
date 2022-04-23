#include "Sequence/PISequenceStep.h"

#include "Misc/Logging.h"

void UPISequenceStep::ExecuteStep()
{
	PI_LOGV_UOBJECT(Error, TEXT("ExecuteStep not implemented"))
}

void UPISequenceStep::Finish()
{
	FinishedDelegate.ExecuteIfBound(this);
}

void UPISequenceStep::BeginPlay(UGameInstance* gameInstance)
{
	_gameInstance = gameInstance;
}

void UPISequenceStep::Execute()
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
