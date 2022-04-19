#pragma once

#include "CoreMinimal.h"
#include "Misc/Logging.h"
#include "SequenceSubsystem.generated.h"

UCLASS()
class PROJETOINDIGENAS_API USequenceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	TMap<TObjectPtr<UObject>, TMap<FName, TWeakObjectPtr<AActor>>> _spawnedActors;

public:
	void RegisterOwner(UObject* owner);
	void UnregisterOwner(const UObject* owner);
	
	void RegisterActor(const UObject* owner, const FName& actorName, AActor* actor);
	void RemoveActor(const UObject* owner, const FName& actorName);

	template<typename TActor>
	TActor* GetActor(const UObject* owner, const FName& actorName)
	{
		TMap<FName, TWeakObjectPtr<AActor>>* mapPtr = _spawnedActors.Find(owner);
		if (mapPtr == nullptr)
		{
			PI_LOG_FMT(TEXT("Sequence controller (%s) not found, returning nullptr"), *owner->GetName())

			return nullptr;
		}

		const TWeakObjectPtr<AActor>* weakPtr = mapPtr->Find(actorName);
		if (weakPtr == nullptr)
		{
			PI_LOG_FMT(TEXT("Actor (%s) not found in map, returning nullptr"), *owner->GetName())

			return nullptr;
		}

		return weakPtr->Get();
	}
};
