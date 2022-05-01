#pragma once

#include "CoreMinimal.h"
#include "PIStateBase.h"

class AWaterBody;
class UPIAnimInstanceBase;

struct PROJETOINDIGENAS_API FPISwimmingStateData
{
	const float CapsuleRadius;
	const float CapsuleRadiusAcceleration;
	const float RotationAcceleration;
	const float MovementSpeedAcceleration;

	FPISwimmingStateData(
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

struct PROJETOINDIGENAS_API FPIWaterBodyInfo
{
	FVector WaterSurfaceLocation;
	FVector WaterSurfaceNormal;
	FVector WaterVelocity;
	float WaterDepth;
};

typedef FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData> FPISwimmingStateBase;

class PROJETOINDIGENAS_API FPISwimmingState : public FPISwimmingStateBase
{
	bool TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const;
	
public:
	TWeakObjectPtr<AWaterBody> WaterBody;
	
	FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate) override;

	virtual void Tick(float DeltaSeconds) override;

	bool CanStartSwimming(const AWaterBody* waterBodyActor);
};
