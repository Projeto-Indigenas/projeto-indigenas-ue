#pragma once

#include "CoreMinimal.h"
#include "PISpawnPawnStep.h"
#include "Beings/Player/PICameraController.h"
#include "PISpawnPlayPawnStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISpawnPlayPawnStep : public UPISpawnPawnStep
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TSubclassOf<APICameraController> _cameraControllerClass;
	
	virtual void PostSpawnActor(UWorld* world, AActor* actor) override;
};
