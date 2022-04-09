#include "ProjetoIndigenasEditor.h"

#include "Debug/PIDebugComponentVisualizer.h"
#include "Debug/PIDebugVisualizationComponent.h"
#include "PathMaker/PIPathMakerEditor.h"

IMPLEMENT_GAME_MODULE(FProjetoIndigenasEditor, ProjetoIndigenasEditor)

void FProjetoIndigenasEditor::StartupModule()
{
	IModuleInterface::StartupModule();

	FEditorModeRegistry::Get().RegisterMode<FPIPathMakerEditor>(
		FPIPathMakerEditor::EditorModeID,
		FText::FromString(TEXT("Path Maker")),
		FSlateIcon(), true);
		
	const FName& componentName = UPIDebugVisualizationComponent::StaticClass()->GetFName();
	GUnrealEd->RegisterComponentVisualizer(componentName, MakeShareable(new FPIDebugComponentVisualizer));
}

void FProjetoIndigenasEditor::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
