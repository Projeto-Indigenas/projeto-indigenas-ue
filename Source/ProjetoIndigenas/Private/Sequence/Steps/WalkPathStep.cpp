#include "Sequence/Steps/WalkPathStep.h"

#include "GameFramework/Character.h"
#include "NPC/PINpcController.h"

void UWalkPathStep::ExecuteStep(const FSequenceQuery& sequenceQuery)
{
	_targetCharacter = _actorProvider->GetActor<APINpcCharacter>(sequenceQuery);

	// TODO(anderson): there should be a error log here
	if (!_targetCharacter.IsValid()) return;

	_targetController = Cast<APINpcController>(_targetCharacter->GetController());
	
	SetupExecutorComponent(_targetCharacter.Get());
}

void UWalkPathStep::BeginPlay(UGameInstance* gameInstance)
{
	Super::BeginPlay(gameInstance);
}

#pragma region IStepExecutor

void UWalkPathStep::BeginExecution()
{
	// TODO(anderson): some logs here too
	if (!_targetController.IsValid()) return;
	
	switch (_targetController->MoveToLocation(_pathData->Nodes[0]))
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

void UWalkPathStep::Tick(float deltaTime)
{
	if (!_targetController.IsValid()) return;

	const UPathFollowingComponent* pathComponent = _targetController->GetPathFollowingComponent();

	if (!pathComponent->HasValidPath()) return;

	const FVector& direction = pathComponent->GetCurrentMoveInput();
	_targetCharacter->SetXInput(direction.Y);
	_targetCharacter->SetYInput(direction.X);
}

#pragma endregion IStepExecutor
