﻿#include "Interactables/PIClimbableTree.h"

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