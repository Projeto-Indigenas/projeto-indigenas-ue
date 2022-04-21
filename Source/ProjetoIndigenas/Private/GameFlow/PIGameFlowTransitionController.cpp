#include "GameFlow/PIGameFlowTransitionController.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Logging.h"
#include "Misc/Nameof.h"

void UPIGameFlowTransitionController::OnOpenLevelCompleted(UWorld*)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(_openLevelHandle);
	_openLevelHandle.Reset();

	OnTransitionCompleted.ExecuteIfBound();
}

void UPIGameFlowTransitionController::Transition(
	const UWorld* world,
	const UPIGameFlowStateData* to)
{
	if (world == nullptr)
	{
		PI_LOGV_UOBJECT(Error, TEXT("Trying to transition with world nullptr"))

		return;
	}

	if (to == nullptr)
	{
		PI_LOGV_UOBJECT(Error, TEXT("Trying to transition to nullptr"))

		return;
	}

	PI_LOGF_UOBJECT(TEXT("Will load persistent level (%s)"), *to->PersistentLevel.GetAssetName())

	_openLevelHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,
			&UPIGameFlowTransitionController::OnOpenLevelCompleted);

	UGameplayStatics::OpenLevelBySoftObjectPtr(world, to->PersistentLevel);
}
