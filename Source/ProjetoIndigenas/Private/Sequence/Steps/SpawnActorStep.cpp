#include "Sequence/Steps/SpawnActorStep.h"

void USpawnActorStep::ExecuteStep()
{
	Super::ExecuteStep();

	GetWorld()->SpawnActor<AActor>(_actorClass, _spawnTransform);

	Finish();
}
