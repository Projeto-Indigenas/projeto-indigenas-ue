#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPINpcAnimationState : uint8
{
	Movement,
	Climbing,
	TurnAround,
};
