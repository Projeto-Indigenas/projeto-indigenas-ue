#pragma once

#include "CoreMinimal.h"
#include "SequenceStep.generated.h"

struct FSequenceQuery;

DECLARE_DELEGATE_OneParam(FSequenceStepFinishedDelegate, class USequenceStep*)
DECLARE_DELEGATE_TwoParams(FSequenceStepSpawnedActorDelegate, const FName&, AActor*)

UCLASS(Abstract, EditInlineNew)
class PROJETOINDIGENAS_API USequenceStep : public UObject
{
    GENERATED_BODY()
    
protected:
    TWeakObjectPtr<UGameInstance> _gameInstance;
    
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    bool _skipStep;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
    float _delay;
    
    virtual void ExecuteStep(const FSequenceQuery* sequenceQuery);
    virtual void Finish();
    
public:
    FSequenceStepFinishedDelegate FinishedDelegate;
    // to be used by subclasses
    FSequenceStepSpawnedActorDelegate SpawnedActorDelegate;
    
    virtual void BeginPlay(UGameInstance* gameInstance);
    void Execute(const FSequenceQuery* sequenceQuery);
};
