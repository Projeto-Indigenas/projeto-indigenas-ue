#include "Debug/PIDebugComponentVisualizer.h"

#include "UnrealEd.h"
#include "Debug/PIDebugVisualizationComponent.h"

void FPIDebugComponentVisualizer::DrawVisualization(
	const UActorComponent* Component,
	const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
 	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(Component);

	if (component == nullptr) return;
	
	component->DrawVisualization(PDI);
}
