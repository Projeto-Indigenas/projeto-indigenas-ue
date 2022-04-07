#include "Sequence/Steps/ToggleActorVisibilityStep.h"

#include "Sequence/Sequence.h"

void UToggleActorVisibilityStep::ExecuteStep(const FSequenceQuery& sequenceQuery)
{
	_targetActor = _actorProvider->GetActor<AActor>(sequenceQuery);

	// TODO(anderson): there should be an error log here
	if (!_targetActor.IsValid()) return;
	
	_targetActor->SetActorHiddenInGame(!_visible);
	
	Finish();
}
