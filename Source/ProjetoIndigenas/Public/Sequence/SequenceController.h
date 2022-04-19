#pragma once

#include "CoreMinimal.h"
#include "Sequence.h"
#include "SequenceController.generated.h"

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API ASequenceController : public AActor
{
	GENERATED_BODY()

	TWeakObjectPtr<USequenceSubsystem> _subsystem;
	
	void DelayToStartTimerAction();
	void SequenceCompleted() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float _delayToStart;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool _startAutomatically;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FSequence _sequence;

	virtual void BeginPlay() override;
	virtual void Destroyed() override;	

public:
	FSequenceCompletedDelegate SequenceCompletedDelegate;

	UFUNCTION(BlueprintCallable)
	void StartSequence();
};
