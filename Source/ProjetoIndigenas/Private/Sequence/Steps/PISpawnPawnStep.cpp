#include "Sequence/Steps/PISpawnPawnStep.h"

#include "AIController.h"
#include "Beings/Player/PICharacter.h"
#include "Beings/Player/PIPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Misc/Logging.h"

void UPISpawnPawnStep::NotifyFinish(APawn* pawn)
{
	_pawnSpawnedDelegate.ExecuteIfBound(pawn);

	Super::Finish();
}

void UPISpawnPawnStep::PostSpawnActor(UWorld* world, AActor* actor)
{
	if (APawn* pawn = Cast<APawn>(actor))
	{
		if (const TSubclassOf<AController>& controllerClass = pawn->AIControllerClass)
		{
			AAIController* controller = world->SpawnActor<AAIController>(controllerClass, pawn->GetActorTransform());

			controller->AttachToActor(pawn, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

			controller->Possess(pawn);
		}

		NotifyFinish(pawn);

		return;
	}

	PI_LOGVF_UOBJECT(Error, TEXT("Pawn is nullptr, actor is not a pawn (%s)"),
		*(actor != nullptr ? actor->GetName() : FString(TEXT("nullptr"))))

	Finish();
}
