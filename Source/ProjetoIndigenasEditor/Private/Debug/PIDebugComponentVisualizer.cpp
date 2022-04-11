#include "Debug/PIDebugComponentVisualizer.h"

#include "SLevelViewport.h"
#include "Debug/PIDebugVisualizationComponent.h"
#include "UnrealEd.h"

bool FPIDebugComponentVisualizer::ShowWhenSelected()
{
	const UActorComponent* actorComponent = GetEditedComponent();
	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(actorComponent);
	if (component == nullptr) return true;
	return component->ShowOnlyWhenSelected;
}

UActorComponent* FPIDebugComponentVisualizer::GetEditedComponent() const
{
	if (!_editingComponent.IsValid()) return nullptr;
	return const_cast<UPIDebugVisualizationComponent*>(_editingComponent.Get());
}

void FPIDebugComponentVisualizer::EndEditing()
{
	if (_editingComponent.IsValid())
	{
		_editingComponent->EndEditing();
	}
	
	_usedViewportClient = nullptr;
	_editingComponent = nullptr;
}

void FPIDebugComponentVisualizer::DrawVisualization(
	const UActorComponent* Component,
	const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	if (_usedViewportClient == nullptr)
	{
		TSharedPtr<FComponentVisualizer> shared = SharedThis<FPIDebugComponentVisualizer>(this);
		FViewportClient* viewportClient = GUnrealEd->GetActiveViewport()->GetClient();
		FEditorViewportClient* editorViewportClient = static_cast<FEditorViewportClient*>(viewportClient);
		GUnrealEd->ComponentVisManager.SetActiveComponentVis(editorViewportClient, shared);
	}
	
	_editingComponent = Cast<UPIDebugVisualizationComponent>(Component);
	if (!_editingComponent.IsValid()) return;
	_editingComponent->DrawVisualization(Component, GCurrentLevelEditingViewportClient, PDI);
}

void FPIDebugComponentVisualizer::DrawVisualizationHUD(
	const UActorComponent* Component,
	const FViewport* Viewport,
	const FSceneView* View,
	FCanvas* Canvas)
{
	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(Component);
	if (component == nullptr) return;
	component->DrawVisualizationHUD(Canvas);
}

bool FPIDebugComponentVisualizer::HandleInputKey(
	FEditorViewportClient* ViewportClient,
	FViewport* Viewport,
	FKey Key,
	EInputEvent Event)
{
	_usedViewportClient = ViewportClient;
	TSharedPtr<FComponentVisualizer> shared = SharedThis<FPIDebugComponentVisualizer>(this);
	GUnrealEd->ComponentVisManager.SetActiveComponentVis(_usedViewportClient, shared);
	const UActorComponent* actorComponent = GetEditedComponent();
	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(actorComponent);
	if (component == nullptr) return false;
	return component->HandleInputKey(ViewportClient, Key, Event);
}
