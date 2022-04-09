#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "EditorOnly/PICustomEditor.h"
#include "Interactables/PIClimbableTree.h"

class PROJETOINDIGENAS_API FPIClimbableTreeCustomEditor : public FPICustomEditor
{
	TWeakObjectPtr<APIClimbableTree> _climbableTree;
	
public:
	explicit FPIClimbableTreeCustomEditor(APIClimbableTree* climbableTree);

	virtual void DrawVisualization(FPrimitiveDrawInterface* PDI) override;
	virtual void DrawVisualizationHUD(FCanvas* Canvas) override;
};

#endif
