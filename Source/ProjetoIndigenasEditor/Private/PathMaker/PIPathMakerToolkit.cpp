#include "PathMaker/PIPathMakerToolkit.h"

#include "EditorModeManager.h"
#include "PathMaker/PIPathMakerEditor.h"
#include "PathMaker/PIPathMakerWidget.h"

FPIPathMakerToolkit::FPIPathMakerToolkit()
{
	SAssignNew(_modeWidget, SPIPathMakerWidget);
}

FName FPIPathMakerToolkit::GetToolkitFName() const
{
	return FName(TEXT("PathMakerToolkit"));
}

FText FPIPathMakerToolkit::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("Path Maker Toolkit"));
}

FEdMode* FPIPathMakerToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FPIPathMakerEditor::EditorModeID);
}

TSharedPtr<SWidget> FPIPathMakerToolkit::GetInlineContent() const
{
	return _modeWidget;
}
