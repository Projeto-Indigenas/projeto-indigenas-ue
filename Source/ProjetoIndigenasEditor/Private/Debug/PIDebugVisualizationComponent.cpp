#include "Debug/PIDebugVisualizationComponent.h"

#include "UnrealEd.h"
#include "Actors/PIActor.h"

UPIDebugVisualizationComponent::UPIDebugVisualizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsEditorOnly = true;
}

void UPIDebugVisualizationComponent::DrawVisualization(FPrimitiveDrawInterface* PDI) const
{
	APIActor* actor = Cast<APIActor>(GetOwner());
	if (actor == nullptr) return;
	actor->DrawVisualization(PDI);
}
