#pragma once

#include "PIGameFlowSettings.h"
#include "PIGameFlowTransitionController.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PIGameFlowSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPIGameFlowTransitionCompletedDelegate,
    const FName&, fromState, const FName&, toState);

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIGameFlowSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    TStrongObjectPtr<const UPIGameFlowData> _gameFlowData;
    TStrongObjectPtr<UPIGameFlowTransitionController> _transitionController;
    
    FName _currentState;

    UFUNCTION() void TransitionCompleted(FName fromState, FName toState);

protected:
    UPROPERTY(BlueprintAssignable)
    FPIGameFlowTransitionCompletedDelegate TransitionCompletedDelegate;
    
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintPure)
    const FName& GetCurrentState() const;
    
    UFUNCTION(BlueprintCallable)
    void TransitionTo(const FName state);
};
