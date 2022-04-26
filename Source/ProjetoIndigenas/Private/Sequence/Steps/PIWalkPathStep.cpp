#include "Sequence/Steps/PIWalkPathStep.h"

#include "Beings/NPC/PINpcController.h"
#include "Misc/Logging.h"

void UPIWalkPathStep::MoveToNextNode()
{
	if (!_destinationController->HasDestination()) return;

	if (_destinationController->IsPathCompleted())
	{
		_targetCharacter->SetInputX(0.f);
		_targetCharacter->SetInputY(0.f);
		
		Finish();

		return;
	}

	FVector vector;
	// TODO(anderson): add some logs here for this failure
	if (!_destinationController->NextDestination(vector)) return;

	// TODO(anderson): some logs here too
	if (!_targetController.IsValid()) return;

	switch (_targetController->MoveToLocation(vector))
	{
	case EPathFollowingRequestResult::Failed:
		UE_LOG(LogTemp, Error, TEXT("AI MoveToLocation result FAILED"));
		break;
	case EPathFollowingRequestResult::AlreadyAtGoal:
		UE_LOG(LogTemp, Warning, TEXT("AI MoveToLocation result ALREADY AT GOAL"));
		break;
	case EPathFollowingRequestResult::RequestSuccessful:
		UE_LOG(LogTemp, Log, TEXT("AI MoveToLocation result SUCCESSFUL"));
		break;
	}
}

void UPIWalkPathStep::PathRequestCompleted(FAIRequestID, const FPathFollowingResult& result)
{
	if (result.IsSuccess())
	{
		MoveToNextNode();

		return;
	}

	if (result.IsFailure() || result.IsInterrupted())
	{
		UE_LOG(LogTemp, Error, TEXT("PathFollowing error: %s"), *result.ToString())
	}
}

void UPIWalkPathStep::ExecuteStep()
{
	Super::ExecuteStep();

	_targetCharacter = GetTargetActor<APINpcCharacter>();
	
	if (!_targetCharacter.IsValid())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Target character is invalid"))

		Finish();
		
		return;
	}

	_targetController = Cast<APINpcController>(_targetCharacter->GetController());
	
	SetupExecutorComponent(_targetCharacter.Get());
}

void UPIWalkPathStep::Finish()
{
	DestroyExecutorComponent();
	
	Super::Finish();
}

void UPIWalkPathStep::BeginPlay(UGameInstance* gameInstance)
{
	Super::BeginPlay(gameInstance);

	_destinationController = MakeUnique<FPIDestinationController>(_pathData->Nodes, _cycleDestinations);
}

#pragma region IStepExecutor

void UPIWalkPathStep::BeginExecution()
{
	if (!_targetController.IsValid()) return;
	
	UPathFollowingComponent* pathComponent = _targetController->GetPathFollowingComponent();
	pathComponent->OnRequestFinished.AddUObject(this, &UPIWalkPathStep::PathRequestCompleted);
	
	MoveToNextNode();
}

void UPIWalkPathStep::Tick(float deltaTime)
{
	if (!_targetController.IsValid()) return;
	if (!_destinationController->HasDestination()) return;

	const UPathFollowingComponent* pathComponent = _targetController->GetPathFollowingComponent();

	const FVector& destination = _destinationController->GetCurrentDestination();
	if (!pathComponent->HasValidPath() && !pathComponent->HasReached(destination))
	{
		_targetCharacter->SetActorLocation(destination);
		
		MoveToNextNode();
		
		return;
	}

	const FVector& direction = pathComponent->GetCurrentMoveInput();
	_targetCharacter->SetInputX(direction.Y);
	_targetCharacter->SetInputY(direction.X);
	_targetCharacter->SetDirectionYaw(direction.Rotation().Yaw);
}

#pragma endregion IStepExecutor
