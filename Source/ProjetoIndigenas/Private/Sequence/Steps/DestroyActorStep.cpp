#include "Sequence/Steps/DestroyActorStep.h"

#include "Misc/Logging.h"

void UDestroyActorStep::ExecuteStep()
{
	if (_targetActor == nullptr)
	{
		PI_LOG_UOBJECT(TEXT("Trying to destroy nullptr actor"))

		return;
	}

	_targetActor->Destroy();

	Finish();
}
