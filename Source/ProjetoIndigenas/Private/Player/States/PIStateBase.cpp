#include "Player/States/PIStateBase.h"

#include "Components/CapsuleComponent.h"
#include "Player/States/PIClimbingState.h"
#include "Player/States/PIMovementState.h"

FPIStateBase::FPIStateBase(APICharacterBase* character)
{
	_character = character;
	_animInstance = Cast<UPIAnimInstanceBase>(_character->GetMesh()->GetAnimInstance());
	_capsuleComponent = _character->GetComponent<UCapsuleComponent>();
}

template <typename TStateData>
FPIStateBaseWithData<TStateData>::FPIStateBaseWithData(APICharacterBase* character, const TStateData& stateData):
	FPIStateBase(character),
	_stateData(stateData)
{
	// nothing yet
}

template class FPIStateBaseWithData<FPIMovementStateData>;
template class FPIStateBaseWithData<FPIClimbingStateData>;
