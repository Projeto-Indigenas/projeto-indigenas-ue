#pragma once

#include "CoreMinimal.h"
#include "PISequenceStep.generated.h"

DECLARE_DELEGATE_OneParam(FPISequenceStepFinishedDelegate, class UPISequenceStep*)

UCLASS(Abstract, BlueprintType, EditInlineNew)
class PROJETOINDIGENAS_API UPISequenceStep : public UObject
{
    GENERATED_BODY()
    
protected:
    TWeakObjectPtr<UGameInstance> _gameInstance;
    
    UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
    bool _skipStep;

    UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
    float _delay;
    
    virtual void ExecuteStep();
    virtual void Finish();
    
public:
    FPISequenceStepFinishedDelegate FinishedDelegate;
    
    virtual void BeginPlay(UGameInstance* gameInstance);
    void Execute();
};
