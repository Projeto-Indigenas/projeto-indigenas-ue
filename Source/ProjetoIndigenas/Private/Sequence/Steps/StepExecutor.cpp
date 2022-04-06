#include "Sequence/Steps/StepExecutor.h"

#include "Sequence/SequenceExecutorComponent.h"

void IStepExecutor::SetupExecutorComponent(AActor* targetActor)
{
	UActorComponent* newComponent = targetActor->AddComponentByClass(USequenceExecutorComponent::StaticClass(),
		false, FTransform::Identity, true);
	_sequenceExecutorComponent = Cast<USequenceExecutorComponent>(newComponent);
	_sequenceExecutorComponent->SetupExecutor(this);
	targetActor->FinishAddComponent(_sequenceExecutorComponent.Get(),
		false, FTransform::Identity);
}
