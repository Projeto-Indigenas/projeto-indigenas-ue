#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimationState.generated.h"

UENUM(BlueprintType)
enum class EPICharacterAnimationState : uint8
{
	Default,
	Movement,
	Climbing,
};
