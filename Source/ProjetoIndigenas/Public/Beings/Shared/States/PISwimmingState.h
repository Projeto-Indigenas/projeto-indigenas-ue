#pragma once

#include "CoreMinimal.h"
#include "PIStateBase.h"
#include "Misc/Vectors.h"

enum class EPICharacterAnimationState : uint8;
struct FPISwimAnimState;
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
	float ImmersionDepth;
	bool IsInWater;
};

typedef FPIAnimatedStateBaseWithData<UPIAnimInstanceBase, FPISwimmingStateData> FPISwimmingStateBase;

class PROJETOINDIGENAS_API FPISwimmingState : public FPISwimmingStateBase
{
	inline static constexpr float _swimSurfaceThreshold = 2.5f;
	inline static constexpr float _swimUnderwaterThreshold = 10.f;
	inline static constexpr float _horizontalLimit = 45.f;
	inline static constexpr float _verticalLimit = 30.f;
	inline static constexpr float _swimmingVerticalLimit = 60.f;
	inline static constexpr float _returnToWaterCooldownTime = 1.f;
	
#if !UE_BUILD_SHIPPING
	inline static int _logKey = 0;
	TAutoConsoleVariable<bool> _swimmingLogsEnabled = TAutoConsoleVariable(
		TEXT("pi.swimming.screenlogs"), false,
		TEXT("Displays debug information about swimming"));
	static int GetLogKey() { return ++_logKey; }
#endif
	
	FAcceleratedValue _acceleratedMovementSpeed = FAcceleratedValue::ZeroValue;
	FAcceleratedVector _acceleratedCharacterDirection = FAcceleratedVector::ZeroVector;
	FAcceleratedVector2D _acceleratedSwimAnimDirection = FAcceleratedVector2D::ZeroVector2D;

	EPICharacterAnimationState* _characterAnimState = nullptr;
	FPISwimAnimState* _swimAnimState = nullptr;

	float _getOutOfWaterTime = 0.f;
	float _movementSpeed = 0.f;
	bool _fastSwim = false;
	FRotator _cameraRotator = FRotator::ZeroRotator;
	
	bool TryGetWaterBodyInfo(const AWaterBody* waterBodyActor, FPIWaterBodyInfo& info) const;
	bool IsReturnToWaterCooldownDue() const;

	void SetVerticalInput(float movementSpeed);
	void SetCameraRotator(FRotator cameraRotator);
	void SetFastSwim();
	void UpdateMovementSpeed();
	void CalculateSwimDirection(const FRotator& targetRotation);
	void CharacterMoveSwim(const float& deltaSeconds, const FRotator& cameraRotation);
	void ConstraintToWater(const FPIWaterBodyInfo& info) const;
	
public:
	TWeakObjectPtr<AWaterBody> WaterBody;
	
	FPISwimmingState(APICharacterBase* character, const FPISwimmingStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate) override;

	virtual void Tick(float DeltaSeconds) override;

	bool CanStartSwimming(const AWaterBody* waterBodyActor) const;
	bool CanEndSwimming(const AWaterBody* waterBodyActor) const;
};
