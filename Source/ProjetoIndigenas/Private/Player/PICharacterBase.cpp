#include "Player/PICharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/PIAnimInstanceBase.h"

void APICharacterBase::UpdateMovementSpeed()
{
	if (_animInstance.IsValid() && _animInstance->IsClimbing)
	{
		_acceleratedMovementSpeed = _inputVector.X;
		
		return;
	}
	
	if (_inputVector == FVector::ZeroVector) _run = false;
	const float runMultiplier = _run ? 2.f : 1.f;
	_acceleratedMovementSpeed = _inputVector.GetClampedToMaxSize(1.f).Size() * runMultiplier;
}

void APICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = Cast<UPIAnimInstanceBase>(GetMesh()->GetAnimInstance());
	_capsuleComponent = GetComponent<UCapsuleComponent>();

	_acceleratedCharacterDirection.SetAcceleration(_rotationAcceleration);
	_acceleratedCapsuleRadius.Acceleration = _capsuleRadiusAcceleration;
	_acceleratedMovementSpeed.Acceleration = _defaultMovementAcceleration;

	_acceleratedCapsuleRadius = _defaultCapsuleRadius;
}

void APICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	_acceleratedCharacterDirection.Tick(DeltaSeconds);
	_acceleratedCapsuleRadius.Tick(DeltaSeconds);
	_acceleratedMovementSpeed.Tick(DeltaSeconds);

	if (_capsuleComponent.IsValid())
	{
		_capsuleComponent->SetCapsuleRadius(_acceleratedCapsuleRadius);
	}

	if (_animInstance.IsValid())
	{
		_animInstance->MovementSpeed = _acceleratedMovementSpeed;

		if (_animInstance->IsClimbing) return;
	}

	if (_inputVector != FVector::ZeroVector)
	{
		const FRotator cameraRotator(0.f, _directionYaw, 0.f);
		const FRotator inputRotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, _inputVector);
		const FRotator targetRotator = cameraRotator + inputRotator;
		
		_acceleratedCharacterDirection = targetRotator.Vector();
		
		SetActorRelativeRotation(_acceleratedCharacterDirection);
	}
}

void APICharacterBase::SetXInput(float x)
{
	_inputVector.Y = x;

	UpdateMovementSpeed();
}

void APICharacterBase::SetYInput(float y)
{
	_inputVector.X = y;

	UpdateMovementSpeed();
}

void APICharacterBase::SetDirectionYaw(const float& directionYaw)
{
	_directionYaw = directionYaw;

	UpdateMovementSpeed();
}

void APICharacterBase::Dodge()
{
	if (!_animInstance.IsValid()) return;

	_animInstance->ShouldDodge = true;
}

void APICharacterBase::ToggleRun()
{
	_run = !_run;

	UpdateMovementSpeed();
}

void APICharacterBase::StartClimbing()
{
	UE_LOG(LogTemp, Error, TEXT("APICharacterBase::%s not implemented"), __func__)
}

void APICharacterBase::StopClimbing()
{
	UE_LOG(LogTemp, Error, TEXT("APICharacterBase::%s not implemented"), __func__)
}

