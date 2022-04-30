#include "Beings/Shared/States/PISwimmingState.h"

#include "Components/CapsuleComponent.h"

#include "WaterBodyActor.h"
#include "Misc/Logging.h"
#include "Beings/Shared/PICharacterBase.h"

bool FPISwimmingState::TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const
{
	const FVector& characterLocation = _character->GetActorLocation();

	waterBodyActor->GetWaterBodyComponent()->GetWaterSurfaceInfoAtLocation(
		characterLocation,
		info.WaterSurfaceLocation,
		info.WaterSurfaceNormal,
		info.WaterVelocity,
		info.WaterDepth,
		true);

	return true;
}

FPISwimmingState::FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData>(character, stateData)
{
	
}

void FPISwimmingState::Enter(FPIInputDelegates& inputDelegates)
{
	FPISwimmingStateBase::Enter(inputDelegates);

	
}

void FPISwimmingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPISwimmingStateBase::Exit(inputDelegates, onExitDelegate);
}

void FPISwimmingState::Tick(float DeltaSeconds)
{
	FPISwimmingStateBase::Tick(DeltaSeconds);
}

bool FPISwimmingState::CanStartSwimming(const AWaterBody* waterBodyActor)
{
	if (!_character.IsValid())
	{
		PI_LOGV(Error, TEXT("Cannot check for swimming without a character"))

		return false;
	}

	if (waterBodyActor == nullptr)
	{
		PI_LOGV(Error, TEXT("Calling swim check without water body actor"))

		return false;
	}
	
	FPIWaterBodyInfo info;
	if (!TryGetWaterBodyInfo(waterBodyActor, info)) return false;

	const float& characterHeight = _character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 2;

	// TODO(anderson): define this percentage somewhere configurable
	return info.WaterDepth >= characterHeight * .7f;
}
