#include "Beings/Player/PIPlayerController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Beings/Player/PICameraController.h"
#include "Beings/Player/PICharacter.h"

void APIPlayerController::MoveXInputBinding(float x)
{
	_inputX = x;
	if (!InputDelegates.IsValid()) return;
	InputDelegates->HorizontalInputDelegate.ExecuteIfBound(_inputX);
}

void APIPlayerController::MoveYInputBinding(float y)
{
	_inputY = y;
	if (!InputDelegates.IsValid()) return;
	InputDelegates->VerticalInputDelegate.ExecuteIfBound(_inputY);
}

void APIPlayerController::ToggleRunInputBinding()
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->ToggleRunDelegate.ExecuteIfBound();
}

void APIPlayerController::DodgeInputBinding()
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->DodgeDelegate.ExecuteIfBound();
}

void APIPlayerController::PositiveActionInputBinding()
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->PositiveActionDelegate.ExecuteIfBound();
}

void APIPlayerController::NegativeActionInputBinding()
{
	if (!InputDelegates.IsValid()) return;
	InputDelegates->NegativeActionDelegate.ExecuteIfBound();
}

void APIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputDelegates = MakeShared<FPIInputDelegates>();

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

	if ((_character = Cast<APICharacter>(InPawn)).IsValid())
	{
		_character->SetInputDelegates(InputDelegates);
	}
}

void APIPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	
	if (_character.IsValid())
	{
		_character->SetInputDelegates(nullptr);
		_character = nullptr;
	}
}

void APIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (InputDelegates.IsValid()) return;
	if (!_cameraController.IsValid()) return;
	
	const FRotator& cameraRotator = _cameraController->GetCameraRotator();
	InputDelegates->CameraRotatorDelegate.ExecuteIfBound(cameraRotator);
	
	FVector inputVector(_inputY, _inputX, 0.f);
	inputVector = cameraRotator.RotateVector(inputVector);

	const FRotator& rotator = inputVector.Rotation();
	const double& pitch = rotator.Pitch;
	const double& yaw = rotator.Yaw;
	InputDelegates->DirectionPitchDelegate.ExecuteIfBound(pitch);
	InputDelegates->DirectionYawDelegate.ExecuteIfBound(yaw);
}

void APIPlayerController::SetCameraController(APICameraController* cameraController)
{
	_cameraController = cameraController;
}

void APIPlayerController::SetAvailableAction(const TSharedPtr<FPIActionBase>& action)
{
	if (_availableAction.IsValid())
	{
		_availableAction->UnbindInput(*InputDelegates);
	}

	_availableAction = action;
	
	if (_availableAction.IsValid())
	{
		_availableAction->BindInput(*InputDelegates);
	}
}
