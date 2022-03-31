#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationState.generated.h"

UENUM(BlueprintType)
enum class ECharacterAnimationState : uint8
{
	Movement,
	Climbing,
};
