#pragma once

#include "CoreMinimal.h"
#include "SequenceExecutorComponent.generated.h"

class IStepExecutor;

UCLASS()
class PROJETOINDIGENAS_API USequenceExecutorComponent : public UActorComponent
{
    GENERATED_BODY()

    IStepExecutor* _stepExecutor;
    
public:
    USequenceExecutorComponent();

    void SetupExecutor(IStepExecutor* stepExecutor);
    
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;
};
