#include "Beings/Player/PIPlayerController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Beings/Player/PICameraController.h"
#include "Beings/Player/PICharacter.h"

void APIPlayerController::MoveXInputBinding(float x)
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->HorizontalInputDelegate.ExecuteIfBound(x);
}

void APIPlayerController::MoveYInputBinding(float y)
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->VerticalInputDelegate.ExecuteIfBound(y);
}

void APIPlayerController::ToggleRunInputBinding()
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->ToggleRunDelegate.ExecuteIfBound();
}

void APIPlayerController::DodgeInputBinding()
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->DodgeDelegate.ExecuteIfBound();
}

void APIPlayerController::PositiveActionInputBinding()
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->PositiveActionDelegate.ExecuteIfBound();
}

void APIPlayerController::NegativeActionInputBinding()
{
	if (!_character.IsValid()) return;
	_character->InputDelegates->NegativeActionDelegate.ExecuteIfBound();
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
	
	if (!_character.IsValid()) return;
	
	_character->InitializeFromController();
}

void APIPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (!_character.IsValid()) return;
	
	_character->InputDelegates = nullptr;
	_character = nullptr;
}

void APIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!_character.IsValid()) return;
	if (!_cameraController.IsValid()) return;

	const APICharacterBase* character = _character.Get();
	const APICameraController* cameraController = _cameraController.Get();

	const double& yaw = cameraController->GetCameraRotator().Yaw;
	character->InputDelegates->DirectionYawDelegate.ExecuteIfBound(yaw);
}

void APIPlayerController::SetCameraControllerConfigureAndSetAsViewTarget(APICameraController* cameraController)
{
	_cameraController = cameraController;
	
	if (cameraController == nullptr) return;
	
	cameraController->SetupPlayerInputComponent(this);

	cameraController->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));

	cameraController->SetTargetActor(GetPawn());

	SetViewTarget(cameraController);
}
