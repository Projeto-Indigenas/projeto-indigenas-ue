#pragma once

#include "CoreMinimal.h"
#include "PISequenceStepBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPISequenceStepFinishedDelegate,
    class UPISequenceStepBase*, step, bool, skipped);

UCLASS(Abstract, BlueprintType)
class PROJETOINDIGENAS_API UPISequenceStepBase : public UObject
{
    GENERATED_BODY()
    
protected:
    TWeakObjectPtr<UGameInstance> _gameInstance;
    
    UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
    bool _skipStep;

    UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
    float _delay;
    
    virtual void ExecuteStep();
    virtual void Finish(const bool& skipped = false);
    
public:
    UPROPERTY(BlueprintAssignable)
    FPISequenceStepFinishedDelegate OnFinished;
    
    virtual void BeginPlay(UGameInstance* gameInstance);
    
    void Execute();
};
