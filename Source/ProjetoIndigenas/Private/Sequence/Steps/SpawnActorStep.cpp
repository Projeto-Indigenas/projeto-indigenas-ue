#include "Sequence/Steps/SpawnActorStep.h"

#include "GameFramework/Character.h"

void USpawnActorStep::ExecuteStep(const FSequenceQuery& sequenceQuery)
{
	// TODO(anderson): some error notification here should be good
	if (ActorClass == nullptr) return;
	if (!ActorPlayerStart.IsValid()) return;
	
	UWorld* world = _gameInstance->GetWorld();

	const FVector& location = ActorPlayerStart->GetActorLocation();
	const FRotator& rotator = ActorPlayerStart->GetActorRotation();
	AActor* actor = world->SpawnActor<AActor>(ActorClass, location, rotator);

	if (SpawnController && actor->IsA<ACharacter>())
	{
		ACharacter* character = Cast<ACharacter>(actor);
		
		AController* controller = world->SpawnActor<AController>(character->AIControllerClass, location, rotator);
		controller->Possess(character);
	}
	
	SpawnedActorDelegate.ExecuteIfBound(ActorName, actor);
	
	Finish();
}
