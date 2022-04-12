﻿#pragma once

#include "CoreMinimal.h"
#include "PIStateBase.h"
#include "Misc/Vectors.h"

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

class PROJETOINDIGENAS_API FPIMovementState : public FPIStateBaseWithData<FPIMovementStateData>
{
	FAcceleratedVector _acceleratedCharacterDirection;
	FAcceleratedValue _acceleratedCapsuleRadius;
	FAcceleratedValue _acceleratedMovementSpeed;

	FVector _inputVector;
	bool _run;
	float _directionYaw;
	
	void UpdateMovementSpeed();

public:
	explicit FPIMovementState(APICharacterBase* character, const FPIMovementStateData& stateData);

	virtual void Tick(float DeltaSeconds) override;

	void SetXInput(float x);
	void SetYInput(float y);
	void ToggleRun();
	void SetDirectionYaw(const float& directionYaw);
	void Dodge() const;
};
