#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.generated.h"

DECLARE_DELEGATE_OneParam(FSequenceStepFinishedDelegate, class USequenceStep*)

UCLASS(EditInlineNew)
class PROJETOINDIGENAS_API USequenceStep : public UObject
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    bool _skipStep;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    float _delay;

protected:
    virtual void ExecuteStep();
    virtual void Finish();
    
public:
    FSequenceStepFinishedDelegate SequenceStepFinishedDelegate;
    
    virtual void BeginPlay();
    void Execute();
};
