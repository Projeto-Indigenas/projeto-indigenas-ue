#include "PathMaker/PIPathMakerEditor.h"

#include <EditorModeManager.h>
#include <FileHelpers.h>

#include "NPC/Paths/PIPathData.h"
#include "PathMaker/PIPathMakerToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "SEditorViewport.h"
#include "Debug/PIPathDrawer.h"

const FEditorModeID FPIPathMakerEditor::EditorModeID = FEditorModeID(TEXT("PathMakerEditorMode"));

FVector FPIPathMakerEditor::GetWorldLocation(const UWorld* world, const FViewportCursorLocation& mouseLocation)
{
	const FVector& mouseOrigin = mouseLocation.GetOrigin();
	const FVector& rayEnd = mouseOrigin + mouseLocation.GetDirection() * 10000.f;
	
	DrawDebugLine(world, mouseOrigin, rayEnd, FColor::Green);

	FHitResult hit;
	if (!world->LineTraceSingleByChannel(hit, mouseOrigin, rayEnd, ECC_WorldStatic))
	{
		return mouseOrigin;
	}

	return hit.Location;
}

void FPIPathMakerEditor::MarkDirty()
{
	if (_targetPath == nullptr) return;

	_targetPath->MarkPackageDirty();
}

void FPIPathMakerEditor::MakeInfoText(const TCHAR* infoText)
{
	if (Toolkit == nullptr) return;

	const FVector* currentNode = GetCurrentNode();
	
	const FString& vectorText = currentNode ? FString::Printf(TEXT(
		"\n"
		"\tX: %.2f\n"
		"\tY: %.2f\n"
		"\tZ: %.2f"
	), currentNode->X, currentNode->Y, currentNode->Z) : FString();

	const FString& infoString = FString::Printf(TEXT(
		"Current node count: %d\n"
		"Current state: %s\n"
		"Current editing node: %s"),
		_targetPath ? _targetPath->Nodes.Num() : 0,
		infoText,
		*vectorText);

	static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetInfoText(infoString);
}

void FPIPathMakerEditor::Save()
{
	FPIPathEditorBase::Save();

	if (_targetPath == nullptr) return;
	
	TArray<UPackage*> toSave;
	toSave.Add(_targetPath->GetPackage());
	UEditorLoadingAndSavingUtils::SavePackages(toSave, true);
}

void FPIPathMakerEditor::Enter()
{
	FEdMode::Enter();
	
	if (!Toolkit.IsValid())
	{
		Toolkit = MakeShareable(new FPIPathMakerToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
	
	MakeInfoText(TEXT("Waiting for path"));
}

void FPIPathMakerEditor::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}

void FPIPathMakerEditor::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{
	FEdMode::Tick(ViewportClient, DeltaTime);

	if (GetCurrentNode() == nullptr) return;

	const FViewportCursorLocation& mouseLocation = ViewportClient->GetCursorWorldLocationFromMousePos();
	const FVector& worldLocation = GetWorldLocation(ViewportClient->GetWorld(), mouseLocation);
	
	SetCurrentNodeValue(worldLocation);
	
	MakeInfoText(TEXT("Placing node"));
}

void FPIPathMakerEditor::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	if (_targetPath == nullptr) return;
	DrawPath(PDI, _targetPath->Nodes);
}

bool FPIPathMakerEditor::InputKey(FEditorViewportClient* ViewportClient,
                                  FViewport* Viewport, FKey Key, EInputEvent Event)
{
	if (_targetPath == nullptr) return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);

	if (Event == IE_Pressed && !Key.IsMouseButton())
	{
		const FViewportCursorLocation& location = ViewportClient->GetCursorWorldLocationFromMousePos();
		const FVector& mouseLocation = GetWorldLocation(ViewportClient->GetWorld(), location);
		
		if (Key == EKeys::N) // new
		{
			CreateNewVector(mouseLocation);
			return true;
		}

		if (Key == EKeys::M) // mark
		{
			FinishPlacingNode();
			return true;
		}

		if (Key == EKeys::G) // grab nearest
		{
			GrabNearestVector(mouseLocation);
			return true;
		}

		if (Key == EKeys::D) // delete nearest
		{
			DeleteNearestVector(mouseLocation);
			return true;
		}

		if (Key == EKeys::F)
		{
			FocusNearestVector(ViewportClient, mouseLocation);
			return true;
		}

		if(Key == EKeys::S)
		{
			Save();
			return true;
		}
	}
	
	return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);
}

TArray<FVector>& FPIPathMakerEditor::GetNodes() const
{
	return _targetPath->Nodes;
}

void FPIPathMakerEditor::SetTargetPath(UPIPathData* targetPath)
{
	_targetPath = targetPath;

	if (targetPath == nullptr)
	{
		MakeInfoText(TEXT("Waiting for path"));

		static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetObjectPath(FString());

		return;
	}

	MakeInfoText(TEXT("Waiting for input"));
	static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetObjectPath(targetPath->GetPathName());
}
