#pragma once

#include "CoreMinimal.h"
#include "PISpawnActorStep.h"
#include "PISpawnPawnStep.generated.h"

class APlayerStart;

DECLARE_DYNAMIC_DELEGATE_OneParam(FPISequenceStepPawnSpawnedDelegate, APawn*, pawn);

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnPawnStep : public UPISpawnActorStep
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	FPISequenceStepPawnSpawnedDelegate _pawnSpawnedDelegate;

	void NotifyFinish(APawn* pawn);

	virtual void PostSpawnActor(UWorld* world, AActor* actor) override;
};
