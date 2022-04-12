#pragma once

#include "CoreMinimal.h"
#include "Misc/Vectors.h"
#include "Beings/Shared/PIStateBase.h"
#include "Beings/Player/PICharacterAnimInstance.h"

struct PROJETOINDIGENAS_API FPIClimbingStateData
{
	const float CapsuleRadius;
	const float CapsuleRadiusAcceleration;
	const float MovementSpeedAcceleration;
	const float RotationAcceleration;

	FPIClimbingStateData(
		const float& capsuleRadius,
		const float& capsuleRadiusAcceleration,
		const float& movementSpeedAcceleration,
		const float& rotationAcceleration)
		: CapsuleRadius(capsuleRadius),
		  CapsuleRadiusAcceleration(capsuleRadiusAcceleration),
		  MovementSpeedAcceleration(movementSpeedAcceleration),
		  RotationAcceleration(rotationAcceleration)
	{ }
};

typedef FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData> FPIClimbableStateBase;

class PROJETOINDIGENAS_API FPIClimbingState : public FPIClimbableStateBase
{
	TWeakObjectPtr<UCharacterMovementComponent> _characterMovement;
	
	FAcceleratedVector2D _acceleratedLocation;
	FAcceleratedVector _acceleratedDirection;
	
	FAcceleratedValue _acceleratedMovementSpeed;
	FAcceleratedValue _acceleratedCapsuleRadius;

	FVector _inputVector;

	void SetInputY(float y);
	void UpdateMovementSpeed();
	
public:
	TWeakObjectPtr<APIClimbableTree> Tree;
	
	explicit FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates) override;

	virtual void Tick(float DeltaSeconds) override;
};
