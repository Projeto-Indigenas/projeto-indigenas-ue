#include "Sequence/Steps/Base/PISequenceStepTargetActorBase.h"

#include "Misc/Logging.h"

void UPISequenceStepTargetActorBase::ExecuteStep()
{
	if (!_targetActorProviderDelegate.IsBound())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Target actor provider delegate is not bound."))

		return;
	}
	
	_targetActor = _targetActorProviderDelegate.Execute();
}
