#include "Debug/PIDebugVisualizationComponent.h"

#include "UnrealEd.h"
#include "Actors/PIActor.h"
#include "EditorOnly/PICustomEditor.h"

UPIDebugVisualizationComponent::UPIDebugVisualizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsEditorOnly = true;
}

void UPIDebugVisualizationComponent::OnRegister()
{
	Super::OnRegister();

	APIActor* actor = Cast<APIActor>(GetOwner());
	if (actor == nullptr) return;
	_customEditor = actor->GetCustomEditor();
}

void UPIDebugVisualizationComponent::DrawVisualization(FPrimitiveDrawInterface* PDI) const
{
	if (!_customEditor.IsValid()) return;
	_customEditor->DrawVisualization(PDI);
}

void UPIDebugVisualizationComponent::DrawVisualizationHUD(FCanvas* Canvas) const
{
	if (!_customEditor.IsValid()) return;
	_customEditor->DrawVisualizationHUD(Canvas);
}
