#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "SpawnActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API USpawnActorStep : public USequenceStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<AActor> _actorClass;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FTransform _spawnTransform;
	
public:
	virtual void ExecuteStep() override;
};
