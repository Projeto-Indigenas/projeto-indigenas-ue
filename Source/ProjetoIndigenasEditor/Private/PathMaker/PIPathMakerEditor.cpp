#include "PathMaker/PIPathMakerEditor.h"

#include "PathMaker/PIPathMakerToolkit.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FPIPathMakerEditor::EditorModeID = FEditorModeID(TEXT("PathMakerEditorMode"));

void FPIPathMakerEditor::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FPIPathMakerToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FPIPathMakerEditor::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}

void FPIPathMakerEditor::SetEditingPath(UPIPathData* pathData)
{
	_editingPath = pathData;
}
