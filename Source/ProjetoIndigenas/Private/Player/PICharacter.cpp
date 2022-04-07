#include "Player/PICharacter.h"

#include "Kismet/KismetMathLibrary.h"

void APICharacter::UpdateMovementSpeed()
{
	if (_inputVector == FVector::ZeroVector) _run = false;
	const float runMultiplier = _run ? 2.f : 1.f;
	MovementSpeed = _inputVector.GetClampedToMaxSize(1.f).Size() * runMultiplier;

	if (!_animInstance.IsValid()) return;
	
	_animInstance->MovementSpeed = MovementSpeed;
}

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = Cast<UPICharacterAnimInstance>(GetMesh()->GetAnimInstance());
	_characterRotator.SetAcceleration(RotationAcceleration);
}

void APICharacter::Tick(float DeltaSeconds)
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

void APICharacter::SetXInput(float x)
{
	_inputVector.Y = x;

	UpdateMovementSpeed();
}

void APICharacter::SetYInput(float y)
{
	_inputVector.X = y;

	UpdateMovementSpeed();
}

void APICharacter::SetDirectionYaw(const float& directionYaw)
{
	_directionYaw = directionYaw;

	UpdateMovementSpeed();
}

void APICharacter::Dodge()
{
	if (!_animInstance.IsValid()) return;

	_animInstance->ShouldDodge = true;
}

void APICharacter::ToggleRun()
{
	_run = !_run;

	UpdateMovementSpeed();
}
