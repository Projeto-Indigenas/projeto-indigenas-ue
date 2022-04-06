#pragma once

#include "CoreMinimal.h"

class USequenceExecutorComponent;

class PROJETOINDIGENAS_API IStepExecutor
{
protected:
	TWeakObjectPtr<USequenceExecutorComponent> _sequenceExecutorComponent;
	
	~IStepExecutor() = default;
	
public:
	virtual void SetupExecutorComponent(AActor* targetActor);

	virtual void BeginExecution() = 0;
	virtual void Tick(float deltaTime) = 0;
};
