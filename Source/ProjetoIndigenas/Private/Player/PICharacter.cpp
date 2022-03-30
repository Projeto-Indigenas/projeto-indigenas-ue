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

void APICharacter::CameraXInputBinding(float value)
{
	_cameraVector.Z = value;
}

void APICharacter::CameraYInputBinding(float value)
{
	_cameraVector.Y = value;
}

void APICharacter::UpdateMovementSpeed() const
{
	if (!_animInstance.IsValid()) return;

	_animInstance->MovementSpeed = _moveVector.Size();
}

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!_springArmComponent.IsValid()) return;
	
	_cameraRotator = _springArmComponent->GetRelativeRotation();
	_animInstance = Cast<UPICharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void APICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("MoveX"), this, &APICharacter::MoveXInputBinding);
	InputComponent->BindAxis(TEXT("MoveY"), this, &APICharacter::MoveYInputBinding);
	InputComponent->BindAxis(TEXT("CameraX"), this, &APICharacter::CameraXInputBinding);
	InputComponent->BindAxis(TEXT("CameraY"), this, &APICharacter::CameraYInputBinding);
}

void APICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_springArmComponent.IsValid()) return;
	
	_cameraRotator.Pitch += _cameraVector.Y * CameraSpeed * DeltaSeconds;
	_cameraRotator.Yaw += _cameraVector.Z * CameraSpeed * DeltaSeconds;
	
	_springArmComponent->SetRelativeRotation(_cameraRotator);
}
