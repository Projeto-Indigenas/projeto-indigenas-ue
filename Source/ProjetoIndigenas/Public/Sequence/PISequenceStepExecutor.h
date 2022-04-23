#pragma once

#include "CoreMinimal.h"

class UPISequenceExecutorComponent;

class PROJETOINDIGENAS_API IPISequenceStepExecutor
{
protected:
	TWeakObjectPtr<UPISequenceExecutorComponent> _sequenceExecutorComponent;
	
	~IPISequenceStepExecutor() = default;
	
public:
	virtual void SetupExecutorComponent(AActor* targetActor);
	virtual void DestroyExecutorComponent();

	virtual void BeginExecution() = 0;
	virtual void Tick(float deltaTime) = 0;
};
