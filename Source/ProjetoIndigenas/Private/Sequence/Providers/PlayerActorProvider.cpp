#include "Sequence/Providers/PlayerActorProvider.h"

AActor* UPlayerActorProvider::GetActor() const
{
	const UWorld* world = GetWorld();
	if (!world) return nullptr;
	const UGameInstance* gameInstance = world->GetGameInstance();
	if (gameInstance == nullptr) return nullptr;
	const ULocalPlayer* localPlayer = gameInstance->GetLocalPlayerByIndex(PlayerIndex);
	if (localPlayer == nullptr) return nullptr;
	const APlayerController* playerController = localPlayer->PlayerController.Get();
	if (playerController == nullptr) return nullptr;
	return playerController->GetPawn();
}
