#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "SequenceController.generated.h"

UCLASS()
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()

	void DelayToStartTimerAction();
	void SequenceCompleted();

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FSequence _sequence;

public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	void StartSequence();
	virtual void BeginPlay() override;
};
