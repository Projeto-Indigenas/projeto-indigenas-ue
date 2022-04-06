#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.generated.h"

DECLARE_DELEGATE_OneParam(FSequenceStepFinishedDelegate, class USequenceStep*)

UCLASS(Abstract, EditInlineNew)
class PROJETOINDIGENAS_API USequenceStep : public UObject
{
    GENERATED_BODY()

    TWeakObjectPtr<UGameInstance> _gameInstance;

protected:
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    bool _skipStep;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    float _delay;
    
    virtual void ExecuteStep();
    virtual void Finish();
    
public:
    FSequenceStepFinishedDelegate SequenceStepFinishedDelegate;
    
    virtual void BeginPlay(UGameInstance* gameInstance);
    void Execute();
};
