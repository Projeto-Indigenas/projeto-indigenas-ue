#include "Sequence/Steps/WalkPathStep.h"

#include "GameFramework/Character.h"
#include "NPC/PINpcController.h"

void UWalkPathStep::MoveToNextNode()
{
	if (!_destinationController->HasDestination()) return;

	if (_destinationController->IsPathCompleted())
	{
		_targetCharacter->SetXInput(0.f);
		_targetCharacter->SetYInput(0.f);
		
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

void UWalkPathStep::PathRequestCompleted(FAIRequestID, const FPathFollowingResult& result)
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

void UWalkPathStep::ExecuteStep(const FSequenceQuery* sequenceQuery)
{
	_targetCharacter = _actorProvider->GetActor<APINpcCharacter>(sequenceQuery);

	// TODO(anderson): there should be a error log here
	if (!_targetCharacter.IsValid()) return;

	_targetController = Cast<APINpcController>(_targetCharacter->GetController());
	
	SetupExecutorComponent(_targetCharacter.Get());
}

void UWalkPathStep::Finish()
{
	DestroyExecutorComponent();
	
	Super::Finish();
}

void UWalkPathStep::BeginPlay(UGameInstance* gameInstance)
{
	Super::BeginPlay(gameInstance);

	_destinationController = MakeUnique<FDestinationController>(_pathData->Nodes, _cycleDestinations);
}

#pragma region IStepExecutor

void UWalkPathStep::BeginExecution()
{
	UPathFollowingComponent* pathComponent = _targetController->GetPathFollowingComponent();
	pathComponent->OnRequestFinished.AddUObject(this, &UWalkPathStep::PathRequestCompleted);
	
	MoveToNextNode();
}

void UWalkPathStep::Tick(float deltaTime)
{
	if (!_targetController.IsValid()) return;

	const UPathFollowingComponent* pathComponent = _targetController->GetPathFollowingComponent();

	const FVector& destination = _destinationController->GetCurrentDestination();
	if (!pathComponent->HasValidPath() && !pathComponent->HasReached(destination))
	{
		_targetCharacter->SetActorLocation(destination);
		
		MoveToNextNode();
		
		return;
	}

	const FVector& direction = pathComponent->GetCurrentMoveInput();
	_targetCharacter->SetXInput(direction.Y);
	_targetCharacter->SetYInput(direction.X);
}

#pragma endregion IStepExecutor
