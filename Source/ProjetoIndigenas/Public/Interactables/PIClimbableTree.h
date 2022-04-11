#pragma once

#include "CoreMinimal.h"
#include "PIClimbableTree.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public AActor
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
	TArray<FVector>& GetTrack() { return _climbableTrack; }
	float GetStartPositionRadius() const { return _startPositionRadius; }
#endif
};
