#include "Actions/PIClimbTreeAction.h"

#include "Interactables/PIClimbableTree.h"
#include "Player/PICharacterBase.h"

FPIClimbTreeAction::FPIClimbTreeAction(APIClimbableTree* targetTree)
{
	_targetTree = targetTree;
}

void FPIClimbTreeAction::Execute()
{
	if (!TargetCharacter.IsValid()) return;
	if (!_targetTree.IsValid()) return;

	TargetCharacter->StartClimbing(_targetTree.Get());
}

void FPIClimbTreeAction::Cancel()
{
	if (!TargetCharacter.IsValid()) return;
	if (!_targetTree.IsValid()) return;

	TargetCharacter->StopClimbing(_targetTree.Get());
}
