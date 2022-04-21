#include "GameFlow/PIGameFlowSubsystem.h"

#include "Misc/Logging.h"

void UPIGameFlowSubsystem::TransitionCompleted(FName fromState, FName toState)
{
	TransitionCompletedDelegate.Broadcast(fromState, toState);

	_currentState = toState;
}

void UPIGameFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UPIGameFlowSettings* settings = GetDefault<UPIGameFlowSettings>();
	_gameFlowData = TStrongObjectPtr(settings->GameFlowData.LoadSynchronous());
	
	_transitionController = TStrongObjectPtr(NewObject<UPIGameFlowTransitionController>(this));
}

const FName& UPIGameFlowSubsystem::GetCurrentState() const
{
	return _currentState;
}

void UPIGameFlowSubsystem::TransitionTo(const FName& state)
{
	if (!_gameFlowData.IsValid())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Game flow data is invalid"))

		return;
	}

	UPIGameFlowStateData*const* toPtr = _gameFlowData->States.Find(state);

	if (toPtr == nullptr)
	{
		PI_LOGV_UOBJECT(Error, TEXT("Trying to transition to nullptr state"))

		return;
	}

	const UPIGameFlowStateData* to = *toPtr;

	_transitionController->OnTransitionCompleted.BindUObject(this,
		&UPIGameFlowSubsystem::TransitionCompleted, _currentState, state);
	
	_transitionController->Transition(GetWorld(), to, _gameFlowData->SharedLevel);
}
