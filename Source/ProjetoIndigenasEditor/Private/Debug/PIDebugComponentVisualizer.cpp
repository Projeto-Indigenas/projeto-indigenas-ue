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
	const USelection* selection = GUnrealEd->GetSelectedObjects();
	if (selection->Num() > 0)
	{
		UObject* object = selection->GetSelectedObject(0);
		UActorComponent* component = Cast<UActorComponent>(object);
		if (component != nullptr)
		{
			return component;
		}
	}

	selection = GUnrealEd->GetSelectedActors();
	if (selection == nullptr || selection->Num() == 0) return nullptr;
	UObject* object = selection->GetSelectedObject(0);
	const AActor* actor = Cast<AActor>(object);
	return actor->GetComponentByClass(UPIDebugVisualizationComponent::StaticClass());
}

void FPIDebugComponentVisualizer::DrawVisualization(
	const UActorComponent* Component,
	const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
 	const UPIDebugVisualizationComponent* component = Cast<UPIDebugVisualizationComponent>(Component);
	if (component == nullptr) return;
	TSharedPtr<FComponentVisualizer> shared = SharedThis<FPIDebugComponentVisualizer>(this);
    FViewportClient* viewportClient = GUnrealEd->GetActiveViewport()->GetClient();
	FEditorViewportClient* editorViewportClient = static_cast<FEditorViewportClient*>(viewportClient);
	GUnrealEd->ComponentVisManager.SetActiveComponentVis(editorViewportClient, shared);
	component->DrawVisualization(editorViewportClient, PDI);
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

bool FPIDebugComponentVisualizer::VisProxyHandleClick(FEditorViewportClient* InViewportClient,
	HComponentVisProxy* VisProxy, const FViewportClick& Click)
{
	return true;
}
