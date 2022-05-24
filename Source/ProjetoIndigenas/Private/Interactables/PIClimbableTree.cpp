#include "Interactables/PIClimbableTree.h"

#include "Actions/PIClimbTreeAction.h"
#include "Beings/Player/PIPlayerController.h"
#include "Beings/Shared/PICharacterBase.h"

void APIClimbableTree::BeginPlay()
{
	Super::BeginPlay();

	_action = MakeShared<FPIClimbTreeAction>(this);

	const UMeshComponent* meshComponent = Cast<UMeshComponent>(GetComponentByClass(UMeshComponent::StaticClass()));

	if (meshComponent == nullptr) return;
	
	for (const FName& socketName : meshComponent->GetAllSocketNames())
	{
		_path.Add(meshComponent->GetSocketLocation(socketName));
	}
}

void APIClimbableTree::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APICharacterBase* targetCharacter = Cast<APICharacterBase>(OtherActor);
	if (targetCharacter == nullptr) return;
	APIPlayerController* playerController = Cast<APIPlayerController>(targetCharacter->GetController());
	if (playerController == nullptr) return;
	_action->TargetCharacter = targetCharacter;
	playerController->SetAvailableAction(_action);
}

void APIClimbableTree::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) const
{
	const APICharacterBase* baseCharacter = Cast<APICharacterBase>(OtherActor);
	if (baseCharacter == nullptr) return;
	APIPlayerController* playerController = Cast<APIPlayerController>(baseCharacter->GetController());
	if (playerController == nullptr) return;
	_action->TargetCharacter = nullptr;
	playerController->SetAvailableAction(nullptr);
}

const TMap<EPIClimbingState, float>& APIClimbableTree::GetPositionRadiusMap() const
{
	return _positionRadiusMap;
}

const TArray<FVector>& APIClimbableTree::GetPath()
{
	return _path;
}
