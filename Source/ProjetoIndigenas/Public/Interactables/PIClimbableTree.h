#pragma once

#include "CoreMinimal.h"
#include "Actions/PIClimbTreeAction.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "PIClimbableTree.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public AActor
{
	GENERATED_BODY()

	TUniquePtr<FPIClimbTreeAction> _action;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPIClimbingState, float> _positionRadiusMap;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) const;

public:
	FORCEINLINE const TMap<EPIClimbingState, float>& GetPositionRadiusMap() const { return _positionRadiusMap; }
};
