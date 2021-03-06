#include "ProjetoIndigenasEditor.h"

#include <UnrealEdGlobals.h>
#include <Editor/UnrealEdEngine.h>

#include "ClimbableTree/PIClimbableTreeCustomEditor.h"
#include "Debug/PIDebugComponentVisualizer.h"
#include "Debug/PIDebugVisualizationComponent.h"
#include "PathMaker/PIPathMakerEditor.h"

IMPLEMENT_GAME_MODULE(FProjetoIndigenasEditor, ProjetoIndigenasEditor)

void FProjetoIndigenasEditor::RegisterCustomEditors()
{
	_customEditors.Add(MakeShareable(new FPIClimbableTreeCustomEditor));
}

void FProjetoIndigenasEditor::StartupModule()
{
	IModuleInterface::StartupModule();

	FEditorModeRegistry::Get().RegisterMode<FPIPathMakerEditor>(
		FPIPathMakerEditor::EditorModeID,
		FText::FromString(TEXT("Path Maker")),
		FSlateIcon(), true);
	
	if (GUnrealEd != nullptr)
	{
		const FName& componentName = UPIDebugVisualizationComponent::StaticClass()->GetFName();
		GUnrealEd->RegisterComponentVisualizer(componentName, MakeShared<FPIDebugComponentVisualizer>());
	}

	RegisterCustomEditors();
}

void FProjetoIndigenasEditor::ShutdownModule()
{
	IModuleInterface::ShutdownModule();

	if (GUnrealEd != nullptr)
	{
		const FName& componentName = UPIDebugVisualizationComponent::StaticClass()->GetFName();
		GUnrealEd->UnregisterComponentVisualizer(componentName);
	}
}

FPICustomEditor* FProjetoIndigenasEditor::GetCustomEditor(UClass* cls) const
{
	for (int index = 0; index < _customEditors.Num(); ++index)
	{
		const TSharedPtr<FPICustomEditor>& customEditor = _customEditors[index];
		if (customEditor->IsEditorForClass(cls)) return customEditor.Get();
	}
	
	return nullptr;
}
