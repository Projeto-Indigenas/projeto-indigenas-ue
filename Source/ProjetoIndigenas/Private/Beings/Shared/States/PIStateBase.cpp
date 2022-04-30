#include "Beings/Shared/States/PIStateBase.h"

#include "Components/CapsuleComponent.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Shared/States/PIMovementState.h"
#include "Beings/Shared/States/PISwimmingState.h"
#include "Beings/Shared/PICharacterBase.h"

void FPIStateBase::InvokeOnExitDelegate() const
{
	_onExitDelegate.ExecuteIfBound();
}

FPIStateBase::FPIStateBase(APICharacterBase* character)
{
	_character = character;
	_capsuleComponent = _character->GetComponent<UCapsuleComponent>();
}

void FPIStateBase::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	_onExitDelegate = onExitDelegate;
}

template <typename TAnimInstance>
FPIAnimatedStateBase<TAnimInstance>::FPIAnimatedStateBase(APICharacterBase* character):
	FPIStateBase(character)
{
	_character = character;
}

template <typename TStateData>
FPIStateBaseWithData<TStateData>::FPIStateBaseWithData(
	APICharacterBase* character,
	const TStateData& stateData):
	FPIStateBase(character),
	_stateData(stateData)
{
	// nothing yet
}

template <typename TAnimInstance, typename TStateData>
FPIAnimatedStateBaseWithData<TAnimInstance, TStateData>::FPIAnimatedStateBaseWithData(
	APICharacterBase* character,
	const TStateData& stateData):
	FPIAnimatedStateBase<TAnimInstance>(character),
	_stateData(stateData)
{
	// nothing yet
}

template class FPIStateBaseWithData<FPIMovementStateData>;
template class FPIStateBaseWithData<FPIClimbingStateData>;
template class FPIAnimatedStateBase<UPICharacterAnimInstance>;
template class FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPIMovementStateData>;
template class FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData>;
template class FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>;
