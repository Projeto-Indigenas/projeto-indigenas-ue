#pragma once

#include "CoreMinimal.h"
#include "PIStateBase.h"
#include "Misc/Vectors.h"

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
	inline static constexpr float _enterSwimThreshold = .4f;
	inline static float _underwaterThreshold = .6f;
	
#if !UE_BUILD_SHIPPING
	inline static int _logKey = 0;
	TAutoConsoleVariable<bool> _swimmingLogsEnabled = TAutoConsoleVariable(
		TEXT("pi.swimming.screenlogs"), false,
		TEXT("Displays debug information about swimming"));
	static int GetLogKey() { return ++_logKey; }
#endif
	
	FAcceleratedValue _acceleratedMovementSpeed = FAcceleratedValue::ZeroValue;
	FAcceleratedVector2D _acceleratedDirection = FAcceleratedVector2D::ZeroVector2D;

	FAcceleratedVector _acceleratedRotation = FAcceleratedVector::ZeroVector;
	
	float _movementSpeed = 0.f;
	bool _fastSwim = false;
	FRotator _cameraRotator = FRotator::ZeroRotator;
	
	bool TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const;

	void SetVerticalInput(float movementSpeed);
	void SetCameraRotator(FRotator cameraRotator);
	void SetFastSwim();
	void UpdateMovementSpeed();
	
public:
	TWeakObjectPtr<AWaterBody> WaterBody;
	
	FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate) override;

	virtual void Tick(float DeltaSeconds) override;

	bool CanStartSwimming(const AWaterBody* waterBodyActor);
};
