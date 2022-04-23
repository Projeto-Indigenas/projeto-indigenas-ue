#pragma once

#include "CoreMinimal.h"
#include "PISpawnActorStep.h"
#include "PISpawnPawnStep.generated.h"

class APlayerStart;

DECLARE_DYNAMIC_DELEGATE_OneParam(FSpawnPawnStepDelegate, APawn*, pawn);

UENUM(BlueprintType)
enum class ESpawnPawnMode : uint8
{
	Free,
	AIControlled,
	PlayerControlled,
};

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnPawnStep : public UPISequenceStep
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
	ESpawnPawnMode _spawnMode;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FSpawnPawnStepDelegate OnSpawnPawnDelegate;
	
public:
	virtual void ExecuteStep() override;
};
