#pragma once

#include "CoreMinimal.h"
#include "PISequenceController.generated.h"

class UPISequenceStepBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPISequenceCompletedDelegate);

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API APISequenceController : public AActor
{
	GENERATED_BODY()

	int _sequenceIndex = -1;

	bool NextIndex();
	UFUNCTION() void StepFinished(UPISequenceStepBase* step, bool skipped);
	
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
	TArray<UPISequenceStepBase*> _steps;

	virtual void BeginPlay() override;
	
	void ExecuteNextStep();

	UFUNCTION(BlueprintCallable)
	void AddStep(UPISequenceStepBase* step);

public:
	UPROPERTY(BlueprintAssignable)
	FPISequenceCompletedDelegate SequenceCompletedDelegate;

	UFUNCTION(BlueprintCallable)
	void StartSequence();

	UFUNCTION(BlueprintNativeEvent)
	void CreateSteps();
};
