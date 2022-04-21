#include "GameFlow/States/PIGameFlowStateBase.h"

void UPIGameFlowStateBase::EnterTransitionCompleted()
{
	if (!_completedDelegate.ExecuteIfBound()) return;
	
	_completedDelegate.Unbind();
}

void UPIGameFlowStateBase::ExitTransitionCompleted()
{
	if (!_completedDelegate.ExecuteIfBound()) return;
	
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
