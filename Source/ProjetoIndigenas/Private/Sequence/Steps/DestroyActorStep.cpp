#include "Sequence/Steps/DestroyActorStep.h"

#include "Misc/Logging.h"

void UDestroyActorStep::ExecuteStep()
{
	if (_targetActor == nullptr)
	{
		PI_LOG_MSG(TEXT("Trying to destroy nullptr actor"))

		return;
	}

	_targetActor->Destroy();

	Finish();
}
