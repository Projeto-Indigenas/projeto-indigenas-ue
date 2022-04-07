#include "Sequence/PISequenceStepExecutor.h"

#include "Sequence/PISequenceExecutorComponent.h"

void IPISequenceStepExecutor::SetupExecutorComponent(AActor* targetActor)
{
	UActorComponent* newComponent = targetActor->AddComponentByClass(UPISequenceExecutorComponent::StaticClass(),
		false, FTransform::Identity, true);
	_sequenceExecutorComponent = Cast<UPISequenceExecutorComponent>(newComponent);
	_sequenceExecutorComponent->SetupExecutor(this);
	targetActor->FinishAddComponent(_sequenceExecutorComponent.Get(),
		false, FTransform::Identity);
}

void IPISequenceStepExecutor::DestroyExecutorComponent()
{
	if (!_sequenceExecutorComponent.IsValid()) return;

	_sequenceExecutorComponent->DestroyComponent();
	_sequenceExecutorComponent.Reset();
}
