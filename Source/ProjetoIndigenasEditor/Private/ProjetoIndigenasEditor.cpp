#include "ProjetoIndigenasEditor.h"

#include <UnrealEdGlobals.h>
#include <Editor/UnrealEdEngine.h>

#include "ClimbableTree/PIClimbableTreeCustomEditor.h"
#include "Debug/PIDebugComponentVisualizer.h"
#include "Debug/PIDebugVisualizationComponent.h"
#include "Interactables/PIClimbableTree.h"
#include "PathMaker/PIPathMakerEditor.h"

IMPLEMENT_GAME_MODULE(FProjetoIndigenasEditor, ProjetoIndigenasEditor)

void FProjetoIndigenasEditor::RegisterCustomEditors()
{
	_customEditorsMap.Add(APIClimbableTree::StaticClass(), MakeShareable(new FPIClimbableTreeCustomEditor));
}

void FProjetoIndigenasEditor::StartupModule()
{
	IModuleInterface::StartupModule();

	FEditorModeRegistry::Get().RegisterMode<FPIPathMakerEditor>(
		FPIPathMakerEditor::EditorModeID,
		FText::FromString(TEXT("Path Maker")),
		FSlateIcon(), true);
		
	const FName& componentName = UPIDebugVisualizationComponent::StaticClass()->GetFName();
	GUnrealEd->RegisterComponentVisualizer(componentName, MakeShareable(new FPIDebugComponentVisualizer));

	RegisterCustomEditors();
}

void FProjetoIndigenasEditor::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
