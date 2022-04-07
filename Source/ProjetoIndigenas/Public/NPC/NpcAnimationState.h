#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENpcAnimationState : uint8
{
	Movement,
	Climbing,
	TurnAround,
};
