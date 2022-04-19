#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.generated.h"

DECLARE_DELEGATE_OneParam(FSequenceStepFinishedDelegate, class USequenceStep*)
DECLARE_DELEGATE_TwoParams(FSequenceStepSpawnedActorDelegate, const FName&, AActor*)

UCLASS(Abstract, BlueprintType, EditInlineNew)
class PROJETOINDIGENAS_API USequenceStep : public UObject
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
    FSequenceStepFinishedDelegate FinishedDelegate;
    
    virtual void BeginPlay(UGameInstance* gameInstance);
    void Execute();
};
