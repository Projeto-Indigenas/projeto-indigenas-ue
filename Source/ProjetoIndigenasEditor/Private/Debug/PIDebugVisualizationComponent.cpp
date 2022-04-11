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
	const FProjetoIndigenasEditor* moduleInstance = static_cast<FProjetoIndigenasEditor*>(module);

	AActor* actor = GetOwner();
	UClass* actorClass = actor->GetClass();
	_customEditor = moduleInstance->GetCustomEditor(actorClass);
	if (_customEditor == nullptr) return;
	_customEditor->SetActor(actor);
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
