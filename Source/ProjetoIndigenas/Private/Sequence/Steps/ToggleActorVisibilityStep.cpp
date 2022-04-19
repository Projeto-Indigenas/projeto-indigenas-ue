#include "Sequence/Steps/ToggleActorVisibilityStep.h"

void UToggleActorVisibilityStep::ExecuteStep()
{
	// TODO(anderson): there should be an error log here
	if (!_targetActor.IsValid()) return;
	
	_targetActor->SetActorHiddenInGame(!_visible);
	
	Finish();
}
