#include "Debug/PIDebugComponentVisualizer.h"

#include "Debug/PIDebugVisualizationComponent.h"
#include "UnrealEd.h"

bool FPIDebugComponentVisualizer::ShowWhenSelected()
{
	const UActorComponent* actorComponent = GetEditedComponent();
	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(actorComponent);
	if (component == nullptr) return true;
	return component->ShowOnlyWhenSelected;
}

void FPIDebugComponentVisualizer::OnRegister()
{
	FComponentVisualizer::OnRegister();
}

UActorComponent* FPIDebugComponentVisualizer::GetEditedComponent() const
{
	USelection* selection = GUnrealEd->GetSelectedActors();
	if (selection == nullptr) return nullptr;
	TArray<UPIDebugVisualizationComponent*> components;
	if (selection->GetSelectedObjects(components) == 0) return nullptr;
	return components[0];
}

void FPIDebugComponentVisualizer::DrawVisualization(
	const UActorComponent* Component,
	const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
 	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(Component);
	if (component == nullptr) return;
	component->DrawVisualization(PDI);
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
	const UActorComponent* actorComponent = GetEditedComponent();
	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(actorComponent);
	if (component == nullptr) return false;
	return component->HandleInputKey(ViewportClient, Key, Event);
}
