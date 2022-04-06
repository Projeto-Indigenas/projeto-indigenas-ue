#include "ProjetoIndigenasEditor.h"
#include "PathMaker/PIPathMakerEditor.h"

IMPLEMENT_GAME_MODULE(FProjetoIndigenasEditor, ProjetoIndigenasEditor)

void FProjetoIndigenasEditor::StartupModule()
{
	IModuleInterface::StartupModule();

	FEditorModeRegistry::Get().RegisterMode<FPIPathMakerEditor>(
		FPIPathMakerEditor::EditorModeID,
		FText::FromString(TEXT("Path Maker Editor")),
		FSlateIcon(), true);
}

void FProjetoIndigenasEditor::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
