#include "Player/PICharacterBase.h"

#include "Player/States/PIStateBase.h"

void APICharacterBase::SetCurrentState(const TSharedPtr<FPIStateBase>& state)
{
	FPIInputDelegates& inputDelegates = *_inputDelegates;
	
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
}

void APICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_currentState.IsValid()) return;

	_currentState->Tick(DeltaSeconds);
}

void APICharacterBase::SetInputDelegates(TSharedPtr<FPIInputDelegates> inputDelegates)
{
	_inputDelegates = inputDelegates;
}
