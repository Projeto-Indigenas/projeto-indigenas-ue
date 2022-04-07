#pragma once

#include "CoreMinimal.h"

class USequenceExecutorComponent;

class PROJETOINDIGENAS_API ISequenceStepExecutor
{
protected:
	TWeakObjectPtr<USequenceExecutorComponent> _sequenceExecutorComponent;
	
	~ISequenceStepExecutor() = default;
	
public:
	virtual void SetupExecutorComponent(AActor* targetActor);

	virtual void BeginExecution() = 0;
	virtual void Tick(float deltaTime) = 0;
};
