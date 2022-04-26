#include "Sequence/Steps/Base/PISequenceStepBase.h"

#include "Misc/Logging.h"

void UPISequenceStepBase::ExecuteStep()
{
	PI_LOGV_UOBJECT(Error, TEXT("ExecuteStep not implemented"))
}

void UPISequenceStepBase::Finish()
{
	if (!OnFinished.IsBound()) return;

	OnFinished.Broadcast(this);
}

void UPISequenceStepBase::BeginPlay(UGameInstance* gameInstance)
{
	_gameInstance = gameInstance;
}

void UPISequenceStepBase::Execute()
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
