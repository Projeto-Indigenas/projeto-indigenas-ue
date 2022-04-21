#include "GameFlow/PIGameFlowTransitionController.h"

#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Logging.h"
#include "Misc/Nameof.h"

void UPIGameFlowTransitionController::OnOpenLevelCompleted(UWorld*)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(_openLevelHandle);
	_openLevelHandle.Reset();

	LoadStreamLevel();
}

void UPIGameFlowTransitionController::LoadStreamLevel()
{
	if (_levelsToLoad.Num() == 0)
	{
		OnTransitionCompleted.ExecuteIfBound();

		return;
	}

	const TSoftObjectPtr<UWorld>& level = _levelsToLoad[0];
	_levelsToLoad.RemoveAt(0);

	const FLatentActionInfo latentInfo(0, 0, NAMEOF(LoadStreamLevel), this);
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, level, true, false, latentInfo);
}

void UPIGameFlowTransitionController::UnloadStreamLevel()
{
	if (_levelsToUnload.Num() == 0)
	{
		LoadStreamLevel();

		return;
	}

	const ULevelStreaming* level = _levelsToUnload[0];
	_levelsToUnload.RemoveAt(0);

	const FLatentActionInfo latentInfo(0, 0, NAMEOF(UnloadStreamLevel), this);
	UGameplayStatics::UnloadStreamLevel(this, level->GetFName(), latentInfo, false);
}

void UPIGameFlowTransitionController::Transition(
	const UWorld* world,
	const UPIGameFlowStateData* to,
	const TSoftObjectPtr<UWorld>& sharedLevel)
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

	const TSoftObjectPtr<UWorld>& persistentLevel = to->PersistentLevel.IsValid() ? to->PersistentLevel : sharedLevel;

	if (!persistentLevel.IsValid())
	{
		PI_LOGVF_UOBJECT(Error, TEXT("Missing persistent level when transitioning to state (%s)"), *to->GetName())

		return;
	}

	const bool& shouldOpenLevel = world->GetFName() != persistentLevel->GetFName();

	const FString& levelAssetName = *persistentLevel.GetAssetName();
	if (shouldOpenLevel) PI_LOGF_UOBJECT(TEXT("Will load persistent level (%s)"), *levelAssetName)
	else PI_LOGF_UOBJECT(TEXT("Will stay on persistent level (%s)"), *levelAssetName)

	if (shouldOpenLevel)
	{
		_levelsToLoad = to->StreamingLevels;
		
		_openLevelHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,
			&UPIGameFlowTransitionController::OnOpenLevelCompleted);

		UGameplayStatics::OpenLevelBySoftObjectPtr(world, persistentLevel);
		
		return;
	}

	_levelsToLoad = to->StreamingLevels;
	_levelsToUnload.Empty();

	ULevelStreaming* each = nullptr;
	auto predicate = [each](TSoftObjectPtr<UWorld> levelToLoad)
	{
		if (each == nullptr) return false;
		return levelToLoad->GetFName() == each->GetFName();
	};

	const TArray<ULevelStreaming*>& levels = world->GetStreamingLevels();
	
	for (int index = 0; index < 0; ++index)
	{
		*&each = levels[index];
		
		if (const TSoftObjectPtr<UWorld>* found = _levelsToLoad.FindByPredicate(predicate))
		{
			PI_LOGF_UOBJECT(TEXT("Stream level (%s) will stay loaded"), *found->Get()->GetFName().ToString())
			
			_levelsToLoad.Remove(*found);

			continue;
		}

		PI_LOGF_UOBJECT(TEXT("Stream level (%s) will be unloaded"), *each->GetFName().ToString())
		
		_levelsToUnload.Add(each);
	}

	UnloadStreamLevel();
}
