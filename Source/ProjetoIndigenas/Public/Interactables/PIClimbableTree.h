#pragma once

#include "CoreMinimal.h"
#include "PIClimbableTree.generated.h"

enum class EPIClimbingState : uint8;
class FPIClimbTreeAction;

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public AActor
{
	GENERATED_BODY()

	TSharedPtr<FPIClimbTreeAction> _action;
	TArray<FVector> _path;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPIClimbingState, float> _positionRadiusMap;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) const;

public:
	FORCEINLINE const TMap<EPIClimbingState, float>& GetPositionRadiusMap() const;
	FORCEINLINE const TArray<FVector>& GetPath();
};
