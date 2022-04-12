#pragma once

#include "CoreMinimal.h"
#include "PIStateBase.h"
#include "Misc/Vectors.h"

struct PROJETOINDIGENAS_API FPIClimbingStateData
{
	const float CapsuleRadius;
	const float CapsuleRadiusAcceleration;
	const float MovementSpeedAcceleration;

	FPIClimbingStateData(
		const float& CapsuleRadius,
		const float& CapsuleRadiusAcceleration,
		const float& MovementSpeedAcceleration)
		: CapsuleRadius(CapsuleRadius),
		  CapsuleRadiusAcceleration(CapsuleRadiusAcceleration),
		  MovementSpeedAcceleration(MovementSpeedAcceleration)
	{ }
};

class PROJETOINDIGENAS_API FPIClimbingState : public FPIStateBaseWithData<FPIClimbingStateData>
{
	FAcceleratedValue _acceleratedMovementSpeed;
	FAcceleratedValue _acceleratedCapsuleRadius;

	FVector _inputVector;
	
	void UpdateMovementSpeed();
	
public:
	explicit FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData);
	
	virtual void Tick(float DeltaSeconds) override;
};
