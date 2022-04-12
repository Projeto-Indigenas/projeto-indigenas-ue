#include "Player/PICharacterBase.h"

#include "Player/States/PIStateBase.h"

void APICharacterBase::SetCurrentState(const TSharedPtr<FPIStateBase>& state)
{
	_currentState = state;
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

