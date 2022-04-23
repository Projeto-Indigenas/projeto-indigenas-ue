#pragma once

#include "CoreMinimal.h"
#include "Sequence/PISequenceStep.h"
#include "PISpawnActorStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnActorStep : public UPISequenceStep
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
