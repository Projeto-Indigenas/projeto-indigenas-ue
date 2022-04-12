#include "Interactables/PIClimbableTree.h"

#include "Player/PICharacterBase.h"

void APIClimbableTree::BeginPlay()
{
	Super::BeginPlay();

	_action = MakeUnique<FPIClimbTreeAction>(this);
}

void APIClimbableTree::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APICharacterBase* targetCharacter = Cast<APICharacterBase>(OtherActor);
	if (targetCharacter == nullptr) return;
	_action->TargetCharacter = targetCharacter;
	targetCharacter->SetAvailableAction(_action.Get());
}

void APIClimbableTree::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor) const
{
	APICharacterBase* baseCharacter = Cast<APICharacterBase>(OtherActor);
	if (baseCharacter == nullptr) return;
	_action->TargetCharacter = nullptr;
	baseCharacter->SetAvailableAction(nullptr);
}
