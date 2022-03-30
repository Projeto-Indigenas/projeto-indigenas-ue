#include "Player/PICharacter.h"

void APICharacter::MoveXInputBinding(float value)
{
	_moveVector.Y = value;

	UpdateMovementSpeed();
}

void APICharacter::MoveYInputBinding(float value)
{
	_moveVector.X = value;
	
	UpdateMovementSpeed();
}

void APICharacter::UpdateMovementSpeed() const
{
	if (!_animInstance.IsValid()) return;

	_animInstance->MovementSpeed = _moveVector.GetClampedToMaxSize(1.f).Size();
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
}

void APICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_cameraController.IsValid()) return;

	_characterRotator.Yaw = _cameraController->GetCameraRotator().Yaw;
	
	SetActorRotation(_characterRotator);
}
