#include "Player/PIPlayerController.h"

#include "Kismet/KismetMathLibrary.h"
#include "Player/PICameraController.h"
#include "Player/PICharacter.h"

void APIPlayerController::MoveXInputBinding(float x)
{
	_inputDelegates->HorizontalInputDelegate.ExecuteIfBound(x);
}

void APIPlayerController::MoveYInputBinding(float y)
{
	_inputDelegates->VerticalInputDelegate.ExecuteIfBound(y);
}

void APIPlayerController::ToggleRunInputBinding()
{
	_inputDelegates->ToggleRunDelegate.ExecuteIfBound();
}

void APIPlayerController::DodgeInputBinding()
{
	_inputDelegates->DodgeDelegate.ExecuteIfBound();
}

void APIPlayerController::PositiveActionInputBinding()
{
	_inputDelegates->PositiveActionDelegate.ExecuteIfBound();
}

void APIPlayerController::NegativeActionInputBinding()
{
	_inputDelegates->NegativeActionDelegate.ExecuteIfBound();
}

void APIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	_inputDelegates = MakeShared<FPIInputDelegates>();
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
	
	_character->InputDelegates = _inputDelegates;
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

	if (!_cameraController.IsValid()) return;
	if (!_character.IsValid()) return;

	const double& yaw = _cameraController->GetCameraRotator().Yaw;
	_inputDelegates->DirectionYawDelegate.ExecuteIfBound(yaw);
}
