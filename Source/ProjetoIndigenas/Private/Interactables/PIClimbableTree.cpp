#include "Interactables/PIClimbableTree.h"

#include "EditorOnly/ClimbableTree/PIClimbableTreeCustomEditor.h"
#include "Player/PICharacterBase.h"

void APIClimbableTree::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APICharacterBase* baseCharacter = Cast<APICharacterBase>(OtherActor);
	if (baseCharacter == nullptr) return;
	baseCharacter->SetCanStartClimbingTree(true);
}

void APIClimbableTree::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APICharacterBase* baseCharacter = Cast<APICharacterBase>(OtherActor);
	if (baseCharacter == nullptr) return;
	baseCharacter->SetCanStartClimbingTree(false);
}


#if WITH_EDITOR
TSharedPtr<FPICustomEditor> APIClimbableTree::GetCustomEditor()
{
	return MakeShared<FPIClimbableTreeCustomEditor>(this);
}
#endif
