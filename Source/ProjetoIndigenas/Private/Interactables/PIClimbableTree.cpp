#include "Interactables/PIClimbableTree.h"

#include "Debug/PIPathDrawer.h"
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
void APIClimbableTree::DrawVisualization(FPrimitiveDrawInterface* PDI)
{
	DrawCircle(PDI, GetActorLocation(), FVector::ForwardVector, FVector::RightVector,
		FLinearColor::Red, _startPositionRadius, 10, 0, 1.f);

	DrawPath(PDI, _climbableTrack);
}
#endif
