#include "Sequence/PISequenceExecutorComponent.h"

#include "Sequence/PISequenceStepExecutor.h"

void UPISequenceExecutorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (_stepExecutor == nullptr) return;

	_stepExecutor->BeginExecution();
}

UPISequenceExecutorComponent::UPISequenceExecutorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPISequenceExecutorComponent::SetupExecutor(IPISequenceStepExecutor* stepExecutor)
{
	_stepExecutor = stepExecutor;
}

void UPISequenceExecutorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (_stepExecutor == nullptr) return;

	_stepExecutor->Tick(DeltaTime);
}
