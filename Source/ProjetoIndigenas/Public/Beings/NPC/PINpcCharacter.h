#pragma once

#include "CoreMinimal.h"
#include "PINpcAnimationState.h"
#include "Beings/Shared/PICharacterBase.h"
#include "PINpcCharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APINpcCharacter : public APICharacterBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPINpcAnimationState, float> _capsuleRadiusForState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPINpcAnimationState, float> _movementAccelerationForState;
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

public:
	virtual void SetInputX(float x) override;
	virtual void SetInputY(float y) override;
	virtual void SetDirectionYaw(float yaw) override;
};
