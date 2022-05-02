#include "Beings/Shared/PICharacterBase.h"

#include <GameFramework/CharacterMovementComponent.h>

#include "WaterBodyActor.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Shared/States/PIMovementState.h"
#include "Beings/Shared/States/PIStateBase.h"
#include "Misc/Logging.h"
#include "Sequence/Steps/PIDestroyActorStep.h"

void APICharacterBase::SetCurrentState(const TSharedPtr<FPIStateBase>& state)
{
	FPIInputDelegates& inputDelegates = *InputDelegates;

	auto setCurrentLambda = [this, state]
	{
		if (this == nullptr) return;
			
		_currentState = state;

		if (_currentState.IsValid())
		{
			_currentState->Enter(*InputDelegates);
		}			
	};
	
	if (_currentState.IsValid())
	{
		_currentState->Exit(inputDelegates, FPIStateOnExitDelegate::CreateWeakLambda(this, setCurrentLambda));

		return;
	}

	setCurrentLambda();
}

void APICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	InputDelegates = MakeUnique<FPIInputDelegates>();
}

void APICharacterBase::CreateMovementState(const float& capsuleRadius, const float& movementAcceleration)
{
	_movementState = MakeShared<FPIMovementState>(this,
		FPIMovementStateData(
			capsuleRadius,
			_capsuleRadiusAcceleration,
			_rotationAcceleration,
			movementAcceleration
		));
}

void APICharacterBase::CreateClimbingState(const float& capsuleRadius, const float& movementAcceleration)
{
	_climbingState = MakeShared<FPIClimbingState>(this,
		FPIClimbingStateData(
			capsuleRadius,
			_capsuleRadiusAcceleration,
			movementAcceleration,
			_rotationAcceleration
		));
}

void APICharacterBase::CreateSwimmingState(const float& capsuleRadius, const float& movementAcceleration)
{
	_swimmingState = MakeShared<FPISwimmingState>(this,
		FPISwimmingStateData(
			capsuleRadius,
			_capsuleRadiusAcceleration,
			_rotationAcceleration,
			movementAcceleration
		));
}

void APICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_currentState.IsValid()) return;

	_currentState->Tick(DeltaSeconds);


	FString mode;
	switch (GetCharacterMovement()->MovementMode.GetValue())
	{
	case MOVE_Walking:
		mode = TEXT("Walking");
		break;
	case MOVE_Swimming:
		mode = TEXT("Swimming");
		break;
	case MOVE_Flying:
		mode = TEXT("Flying");
		break;
	case MOVE_Custom:
		mode = TEXT("Custom");
		break;
	case MOVE_Falling:
		mode = TEXT("Falling");
		break;
	case MOVE_NavWalking:
		mode = TEXT("NavWalking");
		break;
	case MOVE_None:
		mode = TEXT("None");
	default:
		mode = TEXT("Unknown");
		break;
	}
	
	PI_SCREEN_LOG(0, 1.f, TEXT("MovementMode: %s"), *mode)

	

	// TODO(anderson): should this really be here?
	AWaterBody* waterBody = _waterBodyActor.Get();
	
	if (_currentState != _swimmingState && _swimmingState->CanStartSwimming(waterBody))
	{
		StartSwimming(waterBody);

		return;
	}

	if (_swimmingState->CanEndSwimming(waterBody))
	{
		EndSwimming();
	}
}

void APICharacterBase::SetAvailableAction(FPIActionBase* action)
{
	if (_availableAction != nullptr)
	{
		_availableAction->UnbindInput(*InputDelegates);
	}

	_availableAction = action;
	
	if (_availableAction != nullptr)
	{
		_availableAction->BindInput(*InputDelegates);
	}
}

void APICharacterBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	_waterBodyActor = Cast<AWaterBody>(OtherActor);
}

void APICharacterBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (_waterBodyActor.Get() == OtherActor)
	{
		_waterBodyActor = nullptr;
	}
}
