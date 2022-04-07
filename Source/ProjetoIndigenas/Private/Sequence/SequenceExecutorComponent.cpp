#include "Sequence/SequenceExecutorComponent.h"

#include "Sequence/SequenceStepExecutor.h"

USequenceExecutorComponent::USequenceExecutorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USequenceExecutorComponent::SetupExecutor(ISequenceStepExecutor* stepExecutor)
{
	_stepExecutor = stepExecutor;
}

void USequenceExecutorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_stepExecutor == nullptr) return;

	_stepExecutor->BeginExecution();
}

void USequenceExecutorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (_stepExecutor == nullptr) return;

	_stepExecutor->Tick(DeltaTime);
}
