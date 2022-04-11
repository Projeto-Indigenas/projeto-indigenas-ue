#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

class PROJETOINDIGENASEDITOR_API FPIDebugComponentVisualizer : public FComponentVisualizer
{
public:
	virtual bool ShowWhenSelected() override;
	
	virtual UActorComponent* GetEditedComponent() const override;
	
	virtual void DrawVisualization(
		const UActorComponent* Component,
		const FSceneView* View,
		FPrimitiveDrawInterface* PDI) override;

	virtual void DrawVisualizationHUD(
		const UActorComponent* Component,
		const FViewport* Viewport,
		const FSceneView* View,
		FCanvas* Canvas) override;

	virtual bool HandleInputKey(
		FEditorViewportClient* ViewportClient,
		FViewport* Viewport,
		FKey Key,
		EInputEvent Event) override;
		
	virtual bool VisProxyHandleClick(
		FEditorViewportClient* InViewportClient,
		HComponentVisProxy* VisProxy,
		const FViewportClick& Click) override;
};
