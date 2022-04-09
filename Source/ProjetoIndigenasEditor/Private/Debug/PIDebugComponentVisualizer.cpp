#include "Debug/PIDebugComponentVisualizer.h"

#include "UnrealEd.h"
#include "Debug/PIDebugVisualizationComponent.h"

bool FPIDebugComponentVisualizer::TryGetComponent(
	const UActorComponent* component,
	const UPIDebugVisualizationComponent*& outComponent) const
{
	outComponent = Cast<UPIDebugVisualizationComponent>(component);
	return outComponent != nullptr;
}

bool FPIDebugComponentVisualizer::ShowWhenSelected()
{
	const UPIDebugVisualizationComponent* component;
	if (!TryGetComponent(GetEditedComponent(), component)) return true;
	return component->ShowOnlyWhenSelected;
}

void FPIDebugComponentVisualizer::DrawVisualization(
	const UActorComponent* Component,
	const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
 	const UPIDebugVisualizationComponent* component;
	if (!TryGetComponent(Component, component)) return;
	component->DrawVisualization(PDI);
}

void FPIDebugComponentVisualizer::DrawVisualizationHUD(
	const UActorComponent* Component,
	const FViewport* Viewport,
	const FSceneView* View,
	FCanvas* Canvas)
{
	const UPIDebugVisualizationComponent* component;
	if (!TryGetComponent(Component, component)) return;
	component->DrawVisualizationHUD(Canvas);
}
