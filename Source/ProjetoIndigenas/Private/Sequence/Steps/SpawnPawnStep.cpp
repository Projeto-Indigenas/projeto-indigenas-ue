#include "Sequence/Steps/SpawnPawnStep.h"

#include "AIController.h"
#include "Misc/Logging.h"

void USpawnPawnStep::ExecuteStep()
{
	Super::ExecuteStep();

	APawn* pawn = GetWorld()->SpawnActor<APawn>(_pawnClass, _spawnTransform);

	if (pawn == nullptr)
	{
		PI_LOGVF_UOBJECT(Error, TEXT("Couldn't spawn Pawn (%s)"), *_pawnClass->GetName())

		Finish();

		return;
	}

	switch (_spawnMode)
	{
	case ESpawnPawnMode::AIControlled:
		{
			AAIController* controller = GetWorld()->SpawnActor<AAIController>(pawn->AIControllerClass, _spawnTransform);

			controller->AttachToActor(pawn, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

			controller->Possess(pawn);
			
			break;
		}
	case ESpawnPawnMode::PlayerControlled:
		{
			GetWorld()->GetFirstPlayerController()->Possess(pawn);
			
			break;
		}
	default: break;
	}

	OnSpawnPawnDelegate.ExecuteIfBound(pawn);

	Finish();
}
