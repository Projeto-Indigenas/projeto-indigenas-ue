#include "Player/PIPlayerController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Player/PICameraController.h"
#include "Player/PICharacter.h"

void APIPlayerController::MoveXInputBinding(float x)
{
	if (!_character.IsValid()) return;
	_character->SetInputX(x);
}

void APIPlayerController::MoveYInputBinding(float y)
{
	if (!_character.IsValid()) return;
	_character->SetInputY(y);
}

void APIPlayerController::ToggleRunInputBinding()
{
	if (!_character.IsValid()) return;
	_character->ToggleRun();
}

void APIPlayerController::DodgeInputBinding()
{
	if (!_character.IsValid()) return;
	_character->Dodge();
}

void APIPlayerController::PositiveActionInputBinding()
{
	//TODO(anderson): in the future provide an abstract action event that do not need to be specified
	if (!_character.IsValid()) return;
	_character->StartClimbing();
}

void APIPlayerController::NegativeActionInputBinding()
{
	if (!_character.IsValid()) return;
	_character->StopClimbing();
}

void APIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveX"), this,
		&APIPlayerController::MoveXInputBinding);
	InputComponent->BindAxis(TEXT("MoveY"), this,
		&APIPlayerController::MoveYInputBinding);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this,
		&APIPlayerController::ToggleRunInputBinding);
	InputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this,
		&APIPlayerController::DodgeInputBinding);
	InputComponent->BindAction(TEXT("PositiveAction"), IE_Pressed, this,
		&APIPlayerController::PositiveActionInputBinding);
	InputComponent->BindAction(TEXT("NegativeAction"), IE_Pressed, this,
		&APIPlayerController::NegativeActionInputBinding);
	
}

void APIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	_character = Cast<APICharacter>(InPawn);
}

void APIPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	_character = nullptr;
}

void APIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_cameraController.IsValid()) return;
	if (!_character.IsValid()) return;

	_character->SetDirectionYaw(_cameraController->GetCameraRotator().Yaw);
}
