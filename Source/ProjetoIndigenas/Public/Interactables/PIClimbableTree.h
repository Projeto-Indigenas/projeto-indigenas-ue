#pragma once

#include "CoreMinimal.h"
#include "Actors/PIActor.h"
#include "PIClimbableTree.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public APIActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _startPositionRadius = 5.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FVector> _climbableTrack;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

#if WITH_EDITOR
public:
	virtual void DrawVisualization(FPrimitiveDrawInterface* PDI) override;
#endif
};
