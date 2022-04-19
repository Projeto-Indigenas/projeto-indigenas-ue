#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.h"
#include "SequenceController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSequenceCompletedDelegate);

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()

	int _sequenceIndex = -1;

	bool NextIndex();
	void StepFinished(USequenceStep* step);
	
	void DelayToStartTimerAction();
	void SequenceCompleted() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool _loopSteps = false;

	UPROPERTY()
	TArray<USequenceStep*> _steps;

	virtual void BeginPlay() override;
	
	void ExecuteNextStep();

	UFUNCTION(BlueprintCallable)
	void AddStep(USequenceStep* step);

public:
	UPROPERTY(BlueprintAssignable)
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	UFUNCTION(BlueprintCallable)
	void StartSequence();

	UFUNCTION(BlueprintNativeEvent)
	void CreateSteps();
};
