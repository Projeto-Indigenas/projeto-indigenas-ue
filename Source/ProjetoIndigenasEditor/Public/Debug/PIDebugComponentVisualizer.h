#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "PIDebugVisualizationComponent.h"

class PROJETOINDIGENASEDITOR_API FPIDebugComponentVisualizer : public FComponentVisualizer
{
	bool TryGetComponent(const UActorComponent* component, const UPIDebugVisualizationComponent*& outComponent) const;
	
public:
	virtual bool ShowWhenSelected() override;

	virtual void DrawVisualization(
		const UActorComponent* Component,
		const FSceneView* View,
		FPrimitiveDrawInterface* PDI) override;

	virtual void DrawVisualizationHUD(
		const UActorComponent* Component,
		const FViewport* Viewport,
		const FSceneView* View,
		FCanvas* Canvas) override;
};
