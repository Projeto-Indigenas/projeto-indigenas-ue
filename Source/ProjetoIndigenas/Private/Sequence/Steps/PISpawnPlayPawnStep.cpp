#include "Sequence/Steps/PISpawnPlayPawnStep.h"

#include "Beings/Player/PICharacter.h"
#include "Beings/Player/PIPlayerController.h"
#include "Misc/Logging.h"

void UPISpawnPlayPawnStep::PostSpawnActor(UWorld* world, AActor* actor)
{
	if (APawn* pawn = Cast<APawn>(actor))
	{
		APlayerController* controller = GetWorld()->GetFirstPlayerController();

		if (APIPlayerController* playerController = Cast<APIPlayerController>(controller))
		{
			FHitResult hit;
			playerController->K2_SetActorTransform(pawn->GetActorTransform(), false, hit, true);

			playerController->Possess(pawn);

			pawn->AttachToActor(playerController, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			
			if (_cameraControllerClass)
			{
				APICameraController* cameraController = world->SpawnActor<APICameraController>(
					_cameraControllerClass, pawn->GetActorTransform());

				// this call setups input
				playerController->SetCameraControllerAndConfigure(cameraController);
			}
			else
			{
				PI_LOGV_UOBJECT(Warning, TEXT("Camera Controller class is not valid"))
			}
		}
		else
		{
			PI_LOGVF_UOBJECT(Warning, TEXT("Player Controller is not PIPlayerController - (%s)"),
				*(controller != nullptr ? controller->GetName() : FString(TEXT("nullptr"))))
		}

		NotifyFinish(pawn);

		return;
	}

	PI_LOGVF_UOBJECT(Warning, TEXT("Actor is not a Pawn - (%s)"),
		*(actor != nullptr ? actor->GetName() : FString(TEXT("nullptr"))))

	Finish();
}
