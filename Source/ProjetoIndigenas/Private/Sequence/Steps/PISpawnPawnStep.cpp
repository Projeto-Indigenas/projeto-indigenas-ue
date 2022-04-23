#include "Sequence/Steps/PISpawnPawnStep.h"

#include "AIController.h"
#include "GameFramework/PlayerStart.h"
#include "Misc/Logging.h"

void UPISpawnPawnStep::NotifyFinish(APawn* pawn)
{
	OnSpawnPawnDelegate.ExecuteIfBound(pawn);

	Super::Finish();
}

void UPISpawnPawnStep::ExecuteStep()
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
	
	APawn* pawn = GetWorld()->SpawnActor<APawn>(_pawnClass, spawnTransform, spawnParams);

	if (pawn == nullptr)
	{
		PI_LOGVF_UOBJECT(Error, TEXT("Couldn't spawn Pawn (%s)"), *_pawnClass->GetName())

		Finish();

		return;
	}

	switch (_spawnMode)
	{
	case ESpawnPawnMode::Free:
		{
			NotifyFinish(pawn);

			break;
		}
		
	case ESpawnPawnMode::AIControlled:
		{
			AAIController* controller = GetWorld()->SpawnActor<AAIController>(
				pawn->AIControllerClass, spawnTransform, spawnParams);

			controller->AttachToActor(pawn, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

			controller->Possess(pawn);
		}
		
	case ESpawnPawnMode::PlayerControlled:
		{
			APlayerController* controller = GetWorld()->GetFirstPlayerController();

			controller->Possess(pawn);
			
			break;
		}
	default: break;
	}
}
