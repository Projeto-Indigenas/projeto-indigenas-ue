#include "GameFlow/PIGameFlowStateBase.h"

void UPIGameFlowStateBase::EnterTransitionCompleted()
{
	_completedDelegate.ExecuteIfBound();
	_completedDelegate.Unbind();
}

void UPIGameFlowStateBase::ExitTransitionCompleted()
{
	_completedDelegate.ExecuteIfBound();
	_completedDelegate.Unbind();
}

void UPIGameFlowStateBase::Enter(FPIGameFlowStateTransitionDelegate completed)
{
	_completedDelegate = completed;
}

void UPIGameFlowStateBase::Exit(FPIGameFlowStateTransitionDelegate completed)
{
	_completedDelegate = completed;
}
