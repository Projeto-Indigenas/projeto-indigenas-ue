#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

class PROJETOINDIGENASEDITOR_API FPIDebugComponentVisualizer : public FComponentVisualizer
{
public:
	virtual void DrawVisualization(
		const UActorComponent* Component,
		const FSceneView* View,
		FPrimitiveDrawInterface* PDI) override;
};
