#include "Beings/Shared/PICharacterBase.h"

#include "WaterBodyActor.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Shared/States/PIMovementState.h"
#include "Beings/Shared/States/PIStateBase.h"

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
	
	// TODO(anderson): should this really be here?
	AWaterBody* waterBody = _waterBodyActor.Get();
	
	if (_currentState != _swimmingState)
	{
		if (_swimmingState->CanStartSwimming(waterBody))
		{
			StartSwimming(waterBody);
		}
	}

	if (_currentState == _swimmingState)
	{
		if (_swimmingState->CanEndSwimming())
		{
			EndSwimming();
		}
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
	if (_currentState == _swimmingState)
	{
		_swimmingState->WaterBody = _waterBodyActor;
	}
}

void APICharacterBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (_waterBodyActor.Get() == OtherActor)
	{
		_waterBodyActor = nullptr;
	}
}
