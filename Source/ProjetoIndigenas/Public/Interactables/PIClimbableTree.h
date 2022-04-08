#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PIClimbableTree.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
