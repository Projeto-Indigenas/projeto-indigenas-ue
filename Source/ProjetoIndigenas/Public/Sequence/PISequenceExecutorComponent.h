#pragma once

#include "CoreMinimal.h"
#include "PISequenceExecutorComponent.generated.h"

class IPISequenceStepExecutor;

UCLASS()
class PROJETOINDIGENAS_API UPISequenceExecutorComponent : public UActorComponent
{
    GENERATED_BODY()

    IPISequenceStepExecutor* _stepExecutor;

protected:
    virtual void BeginPlay() override;
    
public:
    UPISequenceExecutorComponent();

    void SetupExecutor(IPISequenceStepExecutor* stepExecutor);
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;
};
