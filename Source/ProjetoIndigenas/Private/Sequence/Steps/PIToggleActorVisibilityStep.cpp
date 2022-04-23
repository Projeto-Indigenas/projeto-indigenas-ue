#include "Sequence/Steps/PIToggleActorVisibilityStep.h"

#include "Misc/Logging.h"

void UPIToggleActorVisibilityStep::ExecuteStep()
{
	AActor* actor = GetTargetActor<AActor>();
	
	if (actor == nullptr)
	{
		PI_LOGV_UOBJECT(Error, TEXT("Target actor is nullptr"))
		
		Finish();
		
		return;
	}
	
	actor->SetActorHiddenInGame(!_visible);
	
	Finish();
}
