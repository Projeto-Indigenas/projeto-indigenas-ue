#include "Sequence/Steps/ToggleActorVisibilityStep.h"

void UToggleActorVisibilityStep::ExecuteStep()
{
	_targetActor->SetActorHiddenInGame(!_visible);
}
