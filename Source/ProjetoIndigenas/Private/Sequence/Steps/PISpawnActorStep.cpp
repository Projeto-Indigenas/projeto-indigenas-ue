#include "Sequence/Steps/PISpawnActorStep.h"

#include "GameFramework/PlayerStart.h"
#include "Misc/Logging.h"

void UPISpawnActorStep::PostSpawnActor(UWorld* world, AActor* actor)
{
	Finish();
}

void UPISpawnActorStep::ExecuteStep()
{
	FTransform spawnTransform = FTransform::Identity;
	
	if (_playerStart.IsValid())
	{
		spawnTransform = _playerStart->GetActorTransform();
	}
	else
	{
		PI_LOGVF_UOBJECT(Error, TEXT("Player Start is invalid, spawning at Identity"))
	}
	
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = _spawnCollisionMethod;

	UWorld* world = GetWorld();
	
	AActor* actor = world->SpawnActor<AActor>(_actorClass, spawnTransform, spawnParams);

	PostSpawnActor(world, actor);
}
