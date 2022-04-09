#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"

class PROJETOINDIGENAS_API FPICustomEditor
{
public:
	virtual ~FPICustomEditor() = default;
	virtual void DrawVisualization(FPrimitiveDrawInterface* PDI) = 0;
	virtual void DrawVisualizationHUD(FCanvas* Canvas) { }
};

#endif
