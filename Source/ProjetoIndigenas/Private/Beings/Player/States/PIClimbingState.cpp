#include "Beings/Player/States/PIClimbingState.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Interactables/PIClimbableTree.h"
#include "Misc/Logging.h"

void FPIClimbingState::SetInputY(float y)
{
	if (*_characterAnimState != EPICharacterAnimationState::Climbing) return;

	_inputValue = y;	

	UpdateMovementSpeed();
}

void FPIClimbingState::UpdateMovementSpeed()
{
	if (*_characterAnimState != EPICharacterAnimationState::Climbing) return;
	
	_acceleratedMovementSpeed = _inputValue;
}

void FPIClimbingState::UpdateTargetLocation()
{
	if (!_character.IsValid()) return;
	_acceleratedLocation.SetCurrent(_character->GetActorLocation());
	
	if (!Tree.IsValid()) return;
	const float& positionRadius = Tree->GetPositionRadiusMap()[_currentState];
	_acceleratedLocation = Tree->GetActorLocation() - _startDirection * positionRadius;

#if !UE_BUILD_SHIPPING
	const FVector& current = _acceleratedLocation;
	PI_SCREEN_LOG(_logsEnabled, 10, TEXT("Accelerated Location current: %s"), *current.ToString())
	PI_SCREEN_LOG(_logsEnabled, 10, TEXT("Accelerated Location target: %s"), *_acceleratedLocation.GetTarget2D().ToString());
#endif
}

void FPIClimbingState::SynchronizeCharacterLocation(const float& deltaSeconds)
{
	_acceleratedLocation.Tick(deltaSeconds);
	
	if (!_character.IsValid()) return;
	
	FVector location = _acceleratedLocation;
	location.Z = _character->GetActorLocation().Z;
	_character->SetActorLocation(location);
}

void FPIClimbingState::ClimbingStarted()
{
	_currentState = EPIClimbingState::HangingOnTreeIdle;
	_acceleratedLocation.SetCurrent(_character->GetActorLocation());
	UpdateTargetLocation();
}

void FPIClimbingState::ClimbingEnded()
{
	SetTreeCameraCollision(ECR_Block);

	UPICharacterAnimInstance* animInstance = GetAnimInstance();
	
	if (animInstance != nullptr)
	{
		animInstance->ClimbingStartedDelegate.Unbind();
		animInstance->ClimbingEndedDelegate.Unbind();
	}

	if (_characterMovement.IsValid())
	{
		_characterMovement->MovementMode = MOVE_Walking;
	}

	Tree = nullptr;
	
	InvokeOnExitDelegate();
}

void FPIClimbingState::ClampLocationToPath()
{
	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;

	const TArray<FVector>& path = Tree->GetPath();

	// TODO(anderson): this will only work if the path has only two nodes.
	// For this to work as intended, we need to implement path projections.
	// Here is a good source of knowledge about projections:
	// https://en.m.wikipedia.org/wiki/Distance_from_a_point_to_a_line

	const float& capsuleHalfHeight = _capsuleComponent->GetScaledCapsuleHalfHeight();
	const float& positionRadius = Tree->GetPositionRadiusMap()[_currentState];
	const FVector& radiusVector = _startDirection * positionRadius;
	const FVector& actorLocation = _character->GetActorLocation();
	const FVector& capsuleHalfHeightVector = FVector::UpVector * capsuleHalfHeight;
	const FVector& pathMinLocation = path[0] - radiusVector + capsuleHalfHeightVector;
	const FVector& pathMaxLocation = path.Last() - radiusVector - capsuleHalfHeightVector;
	const float& clampedZ = FMath::Clamp(actorLocation.Z, pathMinLocation.Z, pathMaxLocation.Z);
	const FVector& finalActorLocation = FVector(actorLocation.X, actorLocation.Y, clampedZ);
	_character->SetActorLocation(finalActorLocation);

	_isAtTop = actorLocation.Z >= pathMaxLocation.Z - 5.f;
	_isAtBottom = actorLocation.Z <= pathMinLocation.Z + 5.f;
	
	if (_isAtTop && _inputValue > 0 || _isAtBottom && _inputValue < 0)
	{
		_acceleratedMovementSpeed = 0.f;
	}
}

void FPIClimbingState::SetTreeCameraCollision(ECollisionResponse response) const
{
	if (!Tree.IsValid()) return;
	UMeshComponent* meshComponent = Cast<UMeshComponent>(Tree->GetComponentByClass(UMeshComponent::StaticClass()));
	if (meshComponent == nullptr) return;
	meshComponent->SetCollisionResponseToChannel(ECC_Camera, response);
}

FPIClimbingState::FPIClimbingState(APICharacterBase* character, const FPIClimbingStateData& stateData):
	FPIAnimatedStateBaseWithData<UPICharacterAnimInstance, FPIClimbingStateData>(character, stateData),
	_currentState(EPIClimbingState::None),
	_inputValue(0),
	_isAtTop(false),
	_isAtBottom(false)
{
	_characterMovement = character->GetCharacterMovement();

	_acceleratedDirection.SetAcceleration(stateData.RotationAcceleration);
	_acceleratedLocation.SetAcceleration(stateData.MovementSpeedAcceleration);
	_acceleratedMovementSpeed.Acceleration = stateData.MovementSpeedAcceleration;

	_acceleratedCapsuleRadius.Acceleration = stateData.CapsuleRadiusAcceleration;

	UPICharacterAnimInstance* animInstance = GetAnimInstance();
	if (animInstance != nullptr)
	{
		_characterAnimState = &animInstance->State;
	}
}

void FPIClimbingState::Enter(FPIInputDelegates& inputDelegates)
{
	inputDelegates.VerticalInputDelegate.BindRaw(this, &FPIClimbingState::SetInputY);

	_inputValue = 0.f;
	_currentState = EPIClimbingState::StartClimbing;

	UPICharacterAnimInstance* animInstance = GetAnimInstance();
	
	if (!Tree.IsValid()) return;
	if (!_character.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;
	if (animInstance == nullptr) return;

	animInstance->ClimbingStartedDelegate.BindRaw(this, &FPIClimbingState::ClimbingStarted);
	animInstance->ClimbingEndedDelegate.BindRaw(this, &FPIClimbingState::ClimbingEnded);
	
	_characterMovement->MovementMode = MOVE_Flying;
	
	_acceleratedCapsuleRadius.Current = _capsuleComponent->GetScaledCapsuleRadius();
	_acceleratedCapsuleRadius = _stateData.CapsuleRadius;

	FVector actorLocation = _character->GetActorLocation();
	FVector treeLocation = Tree->GetActorLocation();
	actorLocation.Z = 0;
	treeLocation.Z = 0;
	_startDirection = treeLocation - actorLocation;
	_startDirection.Normalize();

	FVector currentDirection = _character->GetActorRotation().Vector();
	currentDirection.Normalize();
	_acceleratedDirection.SetCurrent(currentDirection);
	_acceleratedDirection = _startDirection;
	
	UpdateTargetLocation();

	SetTreeCameraCollision(ECR_Ignore);
}

void FPIClimbingState::Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate)
{
	FPIClimbingStateBase::Exit(inputDelegates, onExitDelegate);

	if (!_isAtBottom) return;
	
	inputDelegates.VerticalInputDelegate.Unbind();
	
	_inputValue = 0.f;
	_currentState = EPIClimbingState::EndClimbing;
	UpdateTargetLocation();
}

void FPIClimbingState::Tick(float DeltaSeconds)
{
#if !UE_BUILD_SHIPPING
	_logKey = 0;
#endif
	
	_acceleratedDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);

	if (!_character.IsValid()) return;
	if (!_characterMovement.IsValid()) return;
	if (!_capsuleComponent.IsValid()) return;
	
	_characterMovement->Velocity = FVector::ZeroVector;
	_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	_character->SetActorRotation(_acceleratedDirection);

	switch (_currentState)
	{
	case EPIClimbingState::StartClimbing:
		{
			if (*_characterAnimState == EPICharacterAnimationState::Climbing) break;
			
			if (_acceleratedLocation.IsOnTarget(1.f))
			{
				*_characterAnimState = EPICharacterAnimationState::Climbing;

				break;
			}

			SynchronizeCharacterLocation(DeltaSeconds);
			
			break;
		}
	case EPIClimbingState::HangingOnTreeIdle:
	case EPIClimbingState::HangingOnTreeMoving:
		{
			UpdateTargetLocation();
			SynchronizeCharacterLocation(DeltaSeconds);
			ClampLocationToPath();
			
			if (_acceleratedMovementSpeed.Target == 0)
			{
				if (_currentState != EPIClimbingState::HangingOnTreeIdle)
				{
					_currentState = EPIClimbingState::HangingOnTreeIdle;
				}
			}
			else
			{
				if (_currentState != EPIClimbingState::HangingOnTreeMoving)
				{
					_currentState = EPIClimbingState::HangingOnTreeMoving;
				}
			}
			
			break;
		}
	case EPIClimbingState::EndClimbing:
		{
			if (*_characterAnimState == EPICharacterAnimationState::Default) return;
			
			if (_acceleratedLocation.IsOnTarget(1.f))
			{
				*_characterAnimState = EPICharacterAnimationState::Default;

				return;;
			}
			
			SynchronizeCharacterLocation(DeltaSeconds);
		}
	default: return;
	}

	UPICharacterAnimInstance* animInstance = GetAnimInstance();
	
	if (animInstance == nullptr) return;
	
	_acceleratedMovementSpeed.Tick(DeltaSeconds);
	animInstance->MovementSpeed = _acceleratedMovementSpeed;
}
