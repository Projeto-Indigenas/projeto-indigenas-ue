#include "Actions/PIActionBase.h"

#include "Misc/Logging.h"

#define PI_LOGGING_TYPE_NAME() TEXT("FPIActionBase")

void FPIActionBase::BindInput(FPIInputDelegates& inputDelegates)
{
	inputDelegates.PositiveActionDelegate.BindRaw(this, &FPIActionBase::Execute);
}

void FPIActionBase::UnbindInput(FPIInputDelegates& inputDelegates)
{
	inputDelegates.NegativeActionDelegate.Unbind();
}

void FPIActionBase::Execute()
{
	PI_LOGV(Error, TEXT("not implemented"))
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

void FPICancelableActionBase::Cancel()
{
	PI_LOGV(Error, TEXT("not implemented"))
}
