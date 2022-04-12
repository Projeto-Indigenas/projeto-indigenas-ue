#pragma once

#include "CoreMinimal.h"
#include "Player/Input/PIInputDelegates.h"

class PROJETOINDIGENAS_API FPIActionBase
{
public:
	virtual ~FPIActionBase() = default;

	virtual void BindInput(FPIInputDelegates& inputDelegates);
	virtual void UnbindInput(FPIInputDelegates& inputDelegates);
	
	virtual void Execute() = 0;
};

class PROJETOINDIGENAS_API FPICancelableActionBase : public FPIActionBase
{
public:
	virtual void BindInput(FPIInputDelegates& inputDelegates) override;
	virtual void UnbindInput(FPIInputDelegates& inputDelegates) override;
	
	virtual void Cancel() = 0;
};
