#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.h"
#include "SequenceController.generated.h"

DECLARE_DELEGATE(FSequenceCompletedDelegate)

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()

	TWeakObjectPtr<USequenceSubsystem> _subsystem;

	int _sequenceIndex = -1;

	bool NextIndex();
	void StepFinished(USequenceStep* step);
	
	void DelayToStartTimerAction();
	void SequenceCompleted() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _loopSteps = false;

	UPROPERTY()
	TArray<USequenceStep*> _steps;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	void ExecuteNextStep();

	UFUNCTION(BlueprintCallable)
	void AddStep(USequenceStep* step);

public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	UFUNCTION(BlueprintCallable)
	void StartSequence();
};
