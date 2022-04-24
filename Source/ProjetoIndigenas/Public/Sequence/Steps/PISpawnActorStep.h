#pragma once

#include "CoreMinimal.h"
#include "Sequence/Steps/Base/PISequenceStepBase.h"
#include "PISpawnActorStep.generated.h"

class APlayerStart;

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnActorStep : public UPISequenceStepBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<AActor> _actorClass;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<APlayerStart> _playerStart;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	ESpawnActorCollisionHandlingMethod _spawnCollisionMethod;

	virtual void PostSpawnActor(UWorld* world, AActor* actor);
	
public:
	virtual void ExecuteStep() override;
};
