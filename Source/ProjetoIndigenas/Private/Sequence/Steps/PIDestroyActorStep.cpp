#include "Sequence/Steps/PIDestroyActorStep.h"

#include "Misc/Logging.h"

void UPIDestroyActorStep::ExecuteStep()
{
	Super::ExecuteStep();
	
	AActor* actor = GetTargetActor<AActor>();
	
	if (actor == nullptr)
	{
		PI_LOG_UOBJECT(TEXT("Trying to destroy nullptr actor"))

		Finish();

		return;
	}

	actor->Destroy();

	Finish();
}
