#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.h"
#include "PICharacterBase.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public APICharacterBase
{
	GENERATED_BODY()

	TWeakObjectPtr<UPICharacterAnimInstance> _animInstance;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _capsuleRadiusForState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _movementAccelerationForState;
	
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void StartClimbing() override;
	virtual void StopClimbing() override;
};
