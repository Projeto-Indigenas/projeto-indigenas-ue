#include "Debug/PIDebugVisualizationComponent.h"

#include "ProjetoIndigenasEditor.h"
#include "UnrealEd.h"

UPIDebugVisualizationComponent::UPIDebugVisualizationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsEditorOnly = true;
}

void UPIDebugVisualizationComponent::OnRegister()
{
	Super::OnRegister();

	IModuleInterface* module = FModuleManager::Get().GetModule("ProjetoIndigenasEditor");
	if (module == nullptr) return;
	FProjetoIndigenasEditor* piEditor = static_cast<FProjetoIndigenasEditor*>(module);
	
	_customEditor = piEditor->GetCustomEditor<FPICustomEditor>(GetOwner()->GetClass());
}

void UPIDebugVisualizationComponent::DrawVisualization(FPrimitiveDrawInterface* PDI) const
{
	if (_customEditor == nullptr) return;
	_customEditor->DrawVisualization(PDI);
}

void UPIDebugVisualizationComponent::DrawVisualizationHUD(FCanvas* Canvas) const
{
	if (_customEditor == nullptr) return;
	_customEditor->DrawVisualizationHUD(Canvas);
}

bool UPIDebugVisualizationComponent::HandleInputKey(
	FEditorViewportClient* ViewportClient,
	const FKey& Key,
	const EInputEvent& Event) const
{
	if (_customEditor == nullptr) return false;
	return _customEditor->HandleInputKey(ViewportClient, Key, Event);
}
