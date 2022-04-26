﻿#pragma once

#include "CoreMinimal.h"
#include "Misc/Vectors.h"
#include "Beings/Shared/States/PIStateBase.h"
#include "Beings/Player/PICharacterAnimInstance.h"

struct PROJETOINDIGENAS_API FPIMovementStateData
{
	const float CapsuleRadius;
	const float CapsuleRadiusAcceleration;
	const float RotationAcceleration;
	const float MovementSpeedAcceleration;

	FPIMovementStateData(
		const float& capsuleRadius,
		const float& capsuleRadiusAcceleration,
		const float& rotationAcceleration,
		const float& movementSpeedAcceleration):
		CapsuleRadius(capsuleRadius),
		CapsuleRadiusAcceleration(capsuleRadiusAcceleration),
		RotationAcceleration(rotationAcceleration),
		MovementSpeedAcceleration(movementSpeedAcceleration)
	{ }
};

typedef FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPIMovementStateData> FPIMovementStateBase;

class PROJETOINDIGENAS_API FPIMovementState : public FPIMovementStateBase
{
	FAcceleratedVector _acceleratedCharacterDirection;
	FAcceleratedValue _acceleratedCapsuleRadius;
	FAcceleratedValue _acceleratedMovementSpeed;

	FVector _inputVector = FVector::ZeroVector;
	bool _run = false;
	float _directionYaw = false;
	
	void UpdateMovementSpeed();

	void SetXInput(float x);
	void SetYInput(float y);
	void ToggleRun();
	void SetDirectionYaw(float directionYaw);
	void Dodge() const;

public:
	explicit FPIMovementState(APICharacterBase* character, const FPIMovementStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate) override;
	virtual void Tick(float DeltaSeconds) override;
};
