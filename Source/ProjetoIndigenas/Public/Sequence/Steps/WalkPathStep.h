#pragma once

#include "CoreMinimal.h"
#include "StepExecutor.h"
#include "NPC/Paths/PIPathData.h"
#include "Sequence/SequenceStep.h"
#include "WalkPathStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UWalkPathStep : public USequenceStep, public IStepExecutor
{
	GENERATED_BODY()

protected:
	virtual void ExecuteStep() override;
	
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TWeakObjectPtr<AActor> TargetActor;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPIPathData* PathData;

	virtual void BeginPlay(UGameInstance* gameInstance) override;

	virtual void BeginExecution() override;
	virtual void Tick(float deltaTime) override;
};
