#include "Sequence/SequenceStepExecutor.h"

#include "Sequence/SequenceExecutorComponent.h"

void ISequenceStepExecutor::SetupExecutorComponent(AActor* targetActor)
{
	UActorComponent* newComponent = targetActor->AddComponentByClass(USequenceExecutorComponent::StaticClass(),
		false, FTransform::Identity, true);
	_sequenceExecutorComponent = Cast<USequenceExecutorComponent>(newComponent);
	_sequenceExecutorComponent->SetupExecutor(this);
	targetActor->FinishAddComponent(_sequenceExecutorComponent.Get(),
		false, FTransform::Identity);
}

void ISequenceStepExecutor::DestroyExecutorComponent()
{
	if (!_sequenceExecutorComponent.IsValid()) return;

	_sequenceExecutorComponent->DestroyComponent();
	_sequenceExecutorComponent.Reset();
}
