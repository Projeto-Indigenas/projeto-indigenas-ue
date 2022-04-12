#include "Beings/Shared/PICharacterBase.h"

#include "Beings/Shared/PIStateBase.h"

void APICharacterBase::SetCurrentState(const TSharedPtr<FPIStateBase>& state)
{
	FPIInputDelegates& inputDelegates = *InputDelegates;
	
	if (_currentState.IsValid())
	{
		_currentState->Exit(inputDelegates);
	}
	
	_currentState = state;

	if (_currentState.IsValid())
	{
		_currentState->Enter(inputDelegates);
	}
}

void APICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InputDelegates = MakeUnique<FPIInputDelegates>();
}

void APICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_currentState.IsValid()) return;

	_currentState->Tick(DeltaSeconds);
}

void APICharacterBase::SetAvailableAction(FPIActionBase* action)
{
	if (_availableAction != nullptr)
	{
		_availableAction->UnbindInput(*InputDelegates);
	}

	_availableAction = action;
	
	if (_availableAction != nullptr)
	{
		_availableAction->BindInput(*InputDelegates);
	}
}
