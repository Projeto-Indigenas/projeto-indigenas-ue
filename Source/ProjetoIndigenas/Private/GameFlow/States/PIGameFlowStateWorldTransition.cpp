#include "GameFlow/States/PIGameFlowStateWorldTransition.h"

#include "GameMapsSettings.h"
#include "GameFlow/PIGameFlowSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Logging.h"
#include "Misc/Nameof.h"

void UPIGameFlowStateWorldTransition::OnLevelLoaded(UWorld* world)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(_persistentLevelHandle);
	
	if (world->PersistentLevel->GetFName() == _persistentLevel->GetFName())
	{
		DequeueAndLoadStreamingLevel(world);

		return;
	}

	PI_LOG_V_FMT(Error, TEXT("Delegate called for non persistent level (%s)"),
		*world->PersistentLevel->GetFName().ToString())
}

void UPIGameFlowStateWorldTransition::OnTransitionLevelLoaded(UWorld* world)
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.Remove(_persistentLevelHandle);
	
	if (world->PersistentLevel->GetFName() == _settings->TransitionLevel->GetFName())
	{
		ExitTransitionCompleted();

		return;
	}

	PI_LOG_V_FMT(Error, TEXT("Delegate called for non transition level (%s)"),
		*world->PersistentLevel->GetFName().ToString())
}

void UPIGameFlowStateWorldTransition::DequeueAndLoadStreamingLevel(const UWorld* world)
{
	TSoftObjectPtr<UWorld> level;
	if (!_streamingLevelsQueue.Dequeue(level))
	{
		EnterTransitionCompleted();

		return;
	}

	const FLatentActionInfo latentAction(0, 0, NAMEOF(StreamingLevelLoaded), this);
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(world, level, true, false, latentAction);
}

void UPIGameFlowStateWorldTransition::StreamingLevelLoaded()
{
	DequeueAndLoadStreamingLevel(GetWorld());
}

void UPIGameFlowStateWorldTransition::Enter(FPIGameFlowStateTransitionDelegate completed)
{
	Super::Enter(completed);

	if (!_persistentLevel.IsValid())
	{
		PI_LOG_V_MSG(Error, TEXT("Missing persistent level"))

		return;
	}

	PI_LOG_FMT(TEXT("Will load persistent level (%s)"), *_persistentLevel.GetAssetName())
	
	_streamingLevelsQueue.Empty();

	for (const TSoftObjectPtr<UWorld>& each : _streamingLevels)
	{
		PI_LOG_FMT(TEXT("Queueing for streamed level load (%s)"), *each.GetAssetName())

		_streamingLevelsQueue.Enqueue(each);
	}

	const UWorld* world = GetWorld();
	
	if (world == nullptr)
	{
		PI_LOG_V_MSG(Error, TEXT("World nullptr, something is very wrong"))

		return;
	}

	_persistentLevelHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,
		&UPIGameFlowStateWorldTransition::OnLevelLoaded);
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(world, _persistentLevel);
}

void UPIGameFlowStateWorldTransition::Exit(FPIGameFlowStateTransitionDelegate completed)
{
	Super::Exit(completed);

	const UPIGameFlowSettings* settings = GetDefault<UPIGameFlowSettings>();

	if (settings == nullptr)
	{
		PI_LOG_V_MSG(Error, TEXT("settings is nullptr, something is very wrong"))

		return;
	}

	const UWorld* world = GetWorld();

	if (world == nullptr)
	{
		PI_LOG_V_MSG(Error, TEXT("world is nullptr, something is very wrong"))

		return;
	}
	
	_streamingLevelsQueue.Empty();

	_persistentLevelHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,
		&UPIGameFlowStateWorldTransition::OnTransitionLevelLoaded);

	UGameplayStatics::OpenLevelBySoftObjectPtr(world, settings->TransitionLevel);
}

void UPIGameFlowStateWorldTransition::PostLoad()
{
	Super::PostLoad();
	
	_settings = GetDefault<UPIGameFlowSettings>();
}
