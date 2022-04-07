#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "SequenceController.generated.h"

UCLASS()
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()
	
	void DelayToStartTimerAction();
	void SequenceCompleted() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FSequence _sequence;

public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartSequence();
};
