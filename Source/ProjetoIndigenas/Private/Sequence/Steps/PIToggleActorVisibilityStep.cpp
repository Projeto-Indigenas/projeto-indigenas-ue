#include "Sequence/Steps/PIToggleActorVisibilityStep.h"

void UPIToggleActorVisibilityStep::ExecuteStep()
{
	// TODO(anderson): there should be an error log here
	if (!_targetActor.IsValid()) return;
	
	_targetActor->SetActorHiddenInGame(!_visible);
	
	Finish();
}
