#include "Sequence/Steps/PISpawnActorStep.h"

void UPISpawnActorStep::ExecuteStep()
{
	Super::ExecuteStep();

	GetWorld()->SpawnActor<AActor>(_actorClass, _spawnTransform);

	Finish();
}
