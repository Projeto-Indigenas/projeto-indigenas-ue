#include "Actions/PIActionBase.h"

void FPIActionBase::BindInput(FPIInputDelegates& inputDelegates)
{
	inputDelegates.PositiveActionDelegate.BindRaw(this, &FPIActionBase::Execute);
}

void FPIActionBase::UnbindInput(FPIInputDelegates& inputDelegates)
{
	inputDelegates.NegativeActionDelegate.Unbind();
}

void FPICancelableActionBase::BindInput(FPIInputDelegates& inputDelegates)
{
	FPIActionBase::BindInput(inputDelegates);

	inputDelegates.NegativeActionDelegate.BindRaw(this, &FPICancelableActionBase::Cancel);
}

void FPICancelableActionBase::UnbindInput(FPIInputDelegates& inputDelegates)
{
	FPIActionBase::UnbindInput(inputDelegates);

	inputDelegates.NegativeActionDelegate.Unbind();
}
