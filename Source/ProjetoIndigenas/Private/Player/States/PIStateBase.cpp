﻿#include "Player/States/PIStateBase.h"

#include "Components/CapsuleComponent.h"
#include "Player/States/PIClimbingState.h"
#include "Player/States/PIMovementState.h"

FPIStateBase::FPIStateBase(APICharacterBase* character)
{
	_character = character;
	_capsuleComponent = _character->GetComponent<UCapsuleComponent>();
}

template <typename TAnimInstance>
FPIAnimatedStateBase<TAnimInstance>::FPIAnimatedStateBase(APICharacterBase* character):
	FPIStateBase(character)
{
	_animInstance = Cast<TAnimInstance>(_character->GetMesh()->GetAnimInstance());
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
template class FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIMovementStateData>;
template class FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>;
