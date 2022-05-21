#include "Actions/PISkipCutsceneAction.h"

#include "Sequence/Steps/PIPlayLevelSequenceStep.h"

FPISkipCutsceneAction::FPISkipCutsceneAction(UPIPlayLevelSequenceStep* levelSequenceStep)
{
	_levelSequenceStep = levelSequenceStep;
}

void FPISkipCutsceneAction::Cancel()
{
	if (!_levelSequenceStep.IsValid()) return;
	
	_levelSequenceStep->Skip();
}
