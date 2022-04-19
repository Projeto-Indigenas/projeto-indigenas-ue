#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "SpawnActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API USpawnActorStep : public USequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FName _actorName;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<AActor> _actorClass;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _shouldSpawnController;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	UActorProviderBase* _playerStartProvider;
	
public:
	virtual void ExecuteStep() override;
};
