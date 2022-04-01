#include "Player/PICharacter.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void APICharacter::MoveXInputBinding(float value)
{
	_inputVector.Y = value;

	UpdateMovementSpeed();
}

void APICharacter::MoveYInputBinding(float value)
{
	_inputVector.X = value;
	
	UpdateMovementSpeed();
}

void APICharacter::RunInputBinding()
{
	_run = !_run;

	UpdateMovementSpeed();
}

void APICharacter::UpdateMovementSpeed()
{
	if (!_animInstance.IsValid()) return;

	if (_inputVector == FVector::ZeroVector) _run = false;

	const float runMultiplier = _run ? 2.f : 1.f;
	
	MovementSpeed = _inputVector.GetClampedToMaxSize(1.f).Size() * runMultiplier;
	_animInstance->MovementSpeed = MovementSpeed;
}

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	_animInstance = Cast<UPICharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void APICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveX"), this, &APICharacter::MoveXInputBinding);
	PlayerInputComponent->BindAxis(TEXT("MoveY"), this, &APICharacter::MoveYInputBinding);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &APICharacter::RunInputBinding);
}

void APICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_cameraController.IsValid()) return;

	if (_inputVector != FVector::ZeroVector)
	{
		const FRotator cameraRotator(0.f, _cameraController->GetCameraRotator().Yaw, 0.f);
		const FRotator inputRotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, _inputVector);

		_characterRotator = cameraRotator + inputRotator;

		SetActorRelativeRotation(_characterRotator);
	}
}

void APICharacter::SetCameraController(APICameraController* cameraController)
{
	_cameraController = cameraController;
}
