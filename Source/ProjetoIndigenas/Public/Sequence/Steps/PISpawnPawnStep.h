#pragma once

#include "CoreMinimal.h"
#include "PISpawnActorStep.h"
#include "PISpawnPawnStep.generated.h"

class APlayerStart;

DECLARE_DYNAMIC_DELEGATE_OneParam(FPISequenceStepPawnSpawnedDelegate, APawn*, pawn);

UENUM(BlueprintType)
enum class EPISpawnPawnMode : uint8
{
	Free,
	AIControlled,
	PlayerControlled,
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnPawnStep : public UPISequenceStepBase
{
	GENERATED_BODY()

	void NotifyFinish(APawn* pawn);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<APawn> _pawnClass;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<APlayerStart> _playerStart;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	ESpawnActorCollisionHandlingMethod _spawnCollisionMethod;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	EPISpawnPawnMode _spawnMode;

	UPROPERTY(BlueprintReadWrite)
	FPISequenceStepPawnSpawnedDelegate _pawnSpawnedDelegate;
	
public:
	virtual void ExecuteStep() override;
};
