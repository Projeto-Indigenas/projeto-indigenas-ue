#pragma once

#include "CoreMinimal.h"
#include "Player/PICharacterBase.h"
#include "PINpcCharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APINpcCharacter : public APICharacterBase
{
	GENERATED_BODY()

public:
	virtual void StartClimbing() override;
};
