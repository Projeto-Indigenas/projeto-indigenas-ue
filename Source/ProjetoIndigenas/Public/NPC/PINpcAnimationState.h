#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPINpcAnimationState : uint8
{
	Default,
	Movement,
	Climbing,
	TurnAround,
};
