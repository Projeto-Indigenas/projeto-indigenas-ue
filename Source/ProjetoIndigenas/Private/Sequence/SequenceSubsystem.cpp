#include "Sequence/SequenceSubsystem.h"

void USequenceSubsystem::RegisterOwner(UObject* owner)
{
	_spawnedActors.Add(TObjectPtr<UObject>(owner));
}

void USequenceSubsystem::UnregisterOwner(const UObject* owner)
{
	_spawnedActors.Remove(owner);
}

void USequenceSubsystem::RegisterActor(const UObject* owner, const FName& actorName, AActor* actor)
{
	TMap<FName, TWeakObjectPtr<AActor>>* mapPtr = _spawnedActors.Find(owner);
	if (mapPtr == nullptr)
	{
		PI_LOG_FMT(TEXT("Sequence controller (%s) not registered, returning..."), *owner->GetName())

		return;
	}

	if (mapPtr->Contains(actorName))
	{
		PI_LOG_FMT(TEXT("Actor (%s) already registered for sequence controller, replacing..."), *actorName.ToString())
	}
	
	mapPtr->Add(actorName, actor);
}

void USequenceSubsystem::RemoveActor(const UObject* owner, const FName& actorName)
{
	TMap<FName, TWeakObjectPtr<AActor>>* mapPtr = _spawnedActors.Find(owner);
	if (mapPtr == nullptr)
	{
		PI_LOG_FMT(TEXT("Sequence controller (%s) not found"), *owner->GetName());

		return;
	}

	mapPtr->Remove(actorName);
}
