#pragma once

#include "CoreMinimal.h"
#include "SequenceExecutorComponent.generated.h"

class ISequenceStepExecutor;

UCLASS()
class PROJETOINDIGENAS_API USequenceExecutorComponent : public UActorComponent
{
    GENERATED_BODY()

    ISequenceStepExecutor* _stepExecutor;
    
public:
    USequenceExecutorComponent();

    void SetupExecutor(ISequenceStepExecutor* stepExecutor);
    
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;
};
