#include "Beings/Player/PICameraController.h"

void APICameraController::CameraXInputBinding(float value)
{
	_cameraVector.Z = value;
}

void APICameraController::CameraYInputBinding(float value)
{
	_cameraVector.Y = value;
}

void APICameraController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_targetActor.IsValid()) return;
	if (!_springArmComponent.IsValid()) return;

	_cameraRotator.Pitch += _cameraVector.Y * _cameraSpeed * DeltaSeconds;
	_cameraRotator.Yaw += _cameraVector.Z * _cameraSpeed * DeltaSeconds;

	_springArmComponent->SetRelativeRotation(_cameraRotator);
	SetActorRelativeLocation(_targetActor->GetRootComponent()->GetRelativeLocation());
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

void APICameraController::SetCameraRotation(const FRotator& rotator)
{
	_cameraRotator = rotator;
}

void APICameraController::SetTargetActor(AActor* targetActor)
{
	_targetActor = targetActor;

	if (targetActor == nullptr) return;

	const FRotator& actorRotator = targetActor->GetActorRotation();
	_cameraRotator = FRotator(0.f, actorRotator.Yaw, _cameraRotator.Roll);
	SetActorRotation(FRotator::ZeroRotator);
}
