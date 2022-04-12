#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.h"
#include "PICharacterBase.h"
#include "Input/PIInputDelegates.h"
#include "States/PIStateBase.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public APICharacterBase
{
	GENERATED_BODY()

	TMap<EPICharacterAnimationState, TSharedPtr<FPIStateBase>> _characterStates;
	TWeakObjectPtr<UPICharacterAnimInstance> _animInstance;

	TWeakObjectPtr<APIClimbableTree> _climbableTree;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _capsuleRadiusForState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _movementAccelerationForState;
	
	virtual void BeginPlay() override;
	
public:
	virtual void InitializeFromController() override;

	virtual void SetDirectionYaw(float yaw) override;
	
	virtual void StartClimbing() override;
	virtual void StopClimbing() override;

	virtual void SetClimbableTree(APIClimbableTree* tree) override;
};
