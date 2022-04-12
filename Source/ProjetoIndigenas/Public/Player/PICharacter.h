#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.h"
#include "PICharacterBase.h"
#include "States/PIClimbingState.h"
#include "States/PIMovementState.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public APICharacterBase
{
	GENERATED_BODY()

	TSharedPtr<FPIMovementState> _movementState;
	TSharedPtr<FPIClimbingState> _climbingState;
	TWeakObjectPtr<UPICharacterAnimInstance> _animInstance;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _capsuleRadiusForState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _movementAccelerationForState;
	
	virtual void BeginPlay() override;
	
public:
	virtual void InitializeFromController() override;

	virtual void StartClimbing(APIClimbableTree* tree) override;
	virtual void StopClimbing(APIClimbableTree* tree) override;
};
