#include "Player/PICharacterBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Player/PIAnimInstanceBase.h"

void APICharacterBase::UpdateMovementSpeed()
{
	if (_inputVector == FVector::ZeroVector) _run = false;
	const float runMultiplier = _run ? 2.f : 1.f;
	MovementSpeed = _inputVector.GetClampedToMaxSize(1.f).Size() * runMultiplier;

	if (!_animInstance.IsValid()) return;
	
	_animInstance->MovementSpeed = MovementSpeed;
}

void APICharacterBase::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = Cast<UPIAnimInstanceBase>(GetMesh()->GetAnimInstance());
	_characterRotator.SetAcceleration(RotationAcceleration);
}

void APICharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	_characterRotator.Tick(DeltaSeconds);

	if (_inputVector != FVector::ZeroVector)
	{
		const FRotator cameraRotator(0.f, _directionYaw, 0.f);
		const FRotator inputRotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, _inputVector);
		const FRotator targetRotator = cameraRotator + inputRotator;
		
		_characterRotator.SetTarget(targetRotator.Vector());
		
		SetActorRelativeRotation(_characterRotator.GetRotator());
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

void APICharacterBase::SetCanStartClimbingTree(bool canStartClimbing)
{
	_canStartClimbingTree = canStartClimbing;
}
