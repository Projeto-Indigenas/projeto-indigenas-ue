#include "Sequence/Steps/SpawnActorStep.h"

#include "GameFramework/Character.h"

void USpawnActorStep::ExecuteStep()
{
	// TODO(anderson): some error notification here should be good
	if (_actorClass == nullptr) return;
	if (_playerStartProvider == nullptr) return;
	const APlayerStart* playerStart = _playerStartProvider->GetActor<APlayerStart>();
	if (playerStart == nullptr) return;
	
	UWorld* world = GetWorld();
	

	const FVector& location = playerStart->GetActorLocation();
	const FRotator& rotator = playerStart->GetActorRotation();
	AActor* actor = world->SpawnActor<AActor>(_actorClass, location, rotator);

	if (_shouldSpawnController && actor->IsA<ACharacter>())
	{
		ACharacter* character = Cast<ACharacter>(actor);
		
		AController* controller = world->SpawnActor<AController>(character->AIControllerClass, location, rotator);
		controller->Possess(character);
	}
	
	_subsystem->RegisterActor(GetOuter(), _actorName, actor);
	
	Finish();
}
