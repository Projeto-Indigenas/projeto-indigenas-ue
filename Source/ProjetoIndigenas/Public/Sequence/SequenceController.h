#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "SequenceController.generated.h"

UCLASS()
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	USequence* _sequence;

	void DelayToStartTimerAction();
	void SequenceCompleted();

public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	void StartSequence();
	virtual void BeginPlay() override;
};
