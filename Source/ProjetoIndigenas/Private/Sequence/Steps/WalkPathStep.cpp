#include "Sequence/Steps/WalkPathStep.h"
#include "Sequence/SequenceExecutorComponent.h"

void UWalkPathStep::ExecuteStep()
{
	Super::ExecuteStep();

	if (!TargetActor.IsValid()) return;
	
	SetupExecutorComponent(TargetActor.Get());
}

void UWalkPathStep::BeginPlay(UGameInstance* gameInstance)
{
	Super::BeginPlay(gameInstance);
}

#pragma region IStepExecutor

void UWalkPathStep::BeginExecution()
{
	AActor* actor = _sequenceExecutorComponent->GetOwner();
	//TODO(anderson): continue here
}

void UWalkPathStep::Tick(float deltaTime)
{
	
}

#pragma endregion IStepExecutor
