#include "Sequence/Steps/PIDestroyActorStep.h"

#include "Misc/Logging.h"

void UPIDestroyActorStep::ExecuteStep()
{
	if (_targetActor == nullptr)
	{
		PI_LOG_UOBJECT(TEXT("Trying to destroy nullptr actor"))

		return;
	}

	_targetActor->Destroy();

	Finish();
}
