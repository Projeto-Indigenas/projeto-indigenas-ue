#include "Sequence/Steps/DestroyActorStep.h"

void UDestroyActorStep::ExecuteStep()
{
	AActor* actor = _actorProvider->GetActor<AActor>();

	if (actor == nullptr)
	{
		PI_LOG_MSG(TEXT("Trying to destroy nullptr actor"))

		return;
	}

	actor->GetWorld()->DestroyActor(actor);
}
