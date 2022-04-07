#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"

class UPIDebugVisualizationComponent;

class PROJETOINDIGENASEDITOR_API FPIDebugComponentVisualizer : public FComponentVisualizer
{
	FEditorViewportClient* _usedViewportClient = nullptr;
	TWeakObjectPtr<const UPIDebugVisualizationComponent> _editingComponent;
	
public:
	virtual bool ShowWhenSelected() override;
	
	virtual UActorComponent* GetEditedComponent() const override;

	virtual void EndEditing() override;
	
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
};
