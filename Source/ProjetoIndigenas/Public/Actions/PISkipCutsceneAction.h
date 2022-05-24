#pragma once

#include "CoreMinimal.h"
#include "PIActionBase.h"

class UPIPlayLevelSequenceStep;

class PROJETOINDIGENAS_API FPISkipCutsceneAction : public FPICancelableActionBase
{
	TWeakObjectPtr<UPIPlayLevelSequenceStep> _levelSequenceStep;
	
public:
	explicit FPISkipCutsceneAction(UPIPlayLevelSequenceStep* levelSequenceStep);
	virtual void Cancel() override;
};
