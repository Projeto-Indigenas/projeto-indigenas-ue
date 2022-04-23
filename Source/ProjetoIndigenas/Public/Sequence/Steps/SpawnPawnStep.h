#pragma once

#include "CoreMinimal.h"
#include "SpawnActorStep.h"
#include "SpawnPawnStep.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FSpawnPawnStepDelegate, APawn*, pawn);

UENUM(BlueprintType)
enum class ESpawnPawnMode : uint8
{
	Free,
	AIControlled,
	PlayerControlled,
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API USpawnPawnStep : public USequenceStep
{
	GENERATED_BODY()

	void NotifyFinish(APawn* pawn);

	static void Possess(AController* controller, APawn* pawn);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<APawn> _pawnClass;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FTransform _spawnTransform;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	ESpawnPawnMode _spawnMode;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FSpawnPawnStepDelegate OnSpawnPawnDelegate;
	
public:
	virtual void ExecuteStep() override;
};
