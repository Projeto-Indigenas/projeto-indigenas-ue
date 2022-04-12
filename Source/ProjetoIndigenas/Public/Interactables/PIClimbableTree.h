#pragma once

#include "CoreMinimal.h"
#include "Actions/PIClimbTreeAction.h"
#include "PIClimbableTree.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIClimbableTree : public AActor
{
	GENERATED_BODY()

	TUniquePtr<FPIClimbTreeAction> _action;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _startPositionRadius = 5.f;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) const;

#if WITH_EDITOR
public:
	float GetStartPositionRadius() const { return _startPositionRadius; }
#endif
};
