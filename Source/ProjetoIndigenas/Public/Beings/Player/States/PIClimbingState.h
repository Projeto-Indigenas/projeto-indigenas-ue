#pragma once

#include "CoreMinimal.h"
#include "Misc/Vectors.h"
#include "Beings/Shared/PIStateBase.h"
#include "Beings/Player/PICharacterAnimInstance.h"

enum class PROJETOINDIGENAS_API EPIClimbingState
{
	None,
	FloorToTree,
	HangingOnTree,
	TreeToFloor
};

struct PROJETOINDIGENAS_API FPIClimbingStateData
{
	const float CapsuleRadius;
	const float CapsuleRadiusAcceleration;
	const float MovementSpeedAcceleration;
	const float RotationAcceleration;
	const float SynchronizationAcceleration;

	FPIClimbingStateData(
		const float& capsuleRadius,
		const float& capsuleRadiusAcceleration,
		const float& movementSpeedAcceleration,
		const float& rotationAcceleration,
		const float& synchronizationAcceleration)
		: CapsuleRadius(capsuleRadius),
		  CapsuleRadiusAcceleration(capsuleRadiusAcceleration),
		  MovementSpeedAcceleration(movementSpeedAcceleration),
		  RotationAcceleration(rotationAcceleration),
		  SynchronizationAcceleration(synchronizationAcceleration)
	{ }
};

typedef FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData> FPIClimbingStateBase;

class PROJETOINDIGENAS_API FPIClimbingState : public FPIClimbingStateBase
{
	TWeakObjectPtr<UCharacterMovementComponent> _characterMovement;
	
	FAcceleratedVector2D _acceleratedLocation;
	FAcceleratedVector _acceleratedDirection;
	
	FAcceleratedValue _acceleratedMovementSpeed;
	FAcceleratedValue _acceleratedCapsuleRadius;

	EPICharacterAnimationState* _characterAnimState;

	EPIClimbingState _currentState;

	FVector _inputVector;
	FVector _startDirection;
	bool _synchronizeClimbing;

	void SetInputY(float y);
	void UpdateMovementSpeed();
	void UpdateClimbingSynchronizedLocation(bool climbing);

	FORCEINLINE void SynchronizeCharacterLocation(APICharacterBase* character) const;

	void ClimbingStarted();
	void ClimbingEnded();
	void BeginSynchronizingClimbing(); 
	void EndSynchronizingClimbing();
	
public:
	TWeakObjectPtr<APIClimbableTree> Tree;
	
	explicit FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData);

	virtual void Enter(FPIInputDelegates& inputDelegates) override;
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate) override;

	virtual void Tick(float DeltaSeconds) override;
};
