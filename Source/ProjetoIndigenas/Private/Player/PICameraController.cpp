#include "Player/PICameraController.h"

void APICameraController::CameraXInputBinding(float value)
{
	_cameraVector.Z = value;
}

void APICameraController::CameraYInputBinding(float value)
{
	_cameraVector.Y = value;
}

void APICameraController::BeginPlay()
{
	Super::BeginPlay();

	if (!_springArmComponent.IsValid()) return;

	_cameraRotator = _springArmComponent->GetRelativeRotation();
}

void APICameraController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_springArmComponent.IsValid()) return;

	_cameraRotator.Pitch += _cameraVector.Y * _cameraSpeed * DeltaSeconds;
	_cameraRotator.Yaw += _cameraVector.Z * _cameraSpeed * DeltaSeconds;

	_springArmComponent->SetRelativeRotation(_cameraRotator);
}

const FRotator& APICameraController::GetCameraRotator() const
{
	return _cameraRotator;
}

void APICameraController::SetupPlayerInputComponent(APlayerController* playerController)
{
	if (playerController == nullptr) return;

	playerController->InputComponent->BindAxis(TEXT("CameraX"), this, &APICameraController::CameraXInputBinding);
	playerController->InputComponent->BindAxis(TEXT("CameraY"), this, &APICameraController::CameraYInputBinding);
}

void APICameraController::SetTargetCharacter(ACharacter* character)
{
	_targetCharacter = character;
}
