#pragma once

#include "CoreMinimal.h"
#include "PIActionBase.h"

class APIClimbableTree;
class APICharacterBase;

class PROJETOINDIGENAS_API FPIClimbTreeAction : public FPICancelableActionBase
{
	TWeakObjectPtr<APIClimbableTree> _targetTree;
	
public:
	TWeakObjectPtr<APICharacterBase> TargetCharacter;
	
	explicit FPIClimbTreeAction(APIClimbableTree* targetTree);
	
	virtual void Execute() override;
	virtual void Cancel() override;
};
