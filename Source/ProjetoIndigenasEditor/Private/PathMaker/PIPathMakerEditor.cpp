#include "PathMaker/PIPathMakerEditor.h"

#include "PathMaker/PIPathMakerToolkit.h"
#include "Toolkits/ToolkitManager.h"

const FEditorModeID FPIPathMakerEditor::EditorModeID = FEditorModeID(TEXT("PathMakerEditorMode"));

FVector FPIPathMakerEditor::GetWorldPosition(const FViewportCursorLocation& mouseLocation)
{
	FHitResult hit;
	FCollisionQueryParams queryParams;
	if (!GEditor->GetWorld()->LineTraceSingleByChannel(hit, mouseLocation.GetOrigin(),
		mouseLocation.GetDirection() * 1000.f, ECC_WorldStatic))
	{
		return mouseLocation.GetOrigin();
	}

	return hit.Location;
}

int FPIPathMakerEditor::FindNearestPoint(FVector location) const
{
	FVector nearestLocation = FVector::ZeroVector;
	
	int nearestIndex = -1;
	for (int index = 0; index < _targetPath->Nodes.Num(); ++index)
	{
		const FVector& currentLocation = _targetPath->Nodes[index];
		if (FVector::Distance(currentLocation, location) < FVector::Distance(nearestLocation, location))
		{
			nearestIndex = index;
			nearestLocation = currentLocation;
		}
	}
	
	return nearestIndex;
}

void FPIPathMakerEditor::CreateNewNode(FVector location)
{
	if (_currentNode != nullptr) return;

	if (_targetPath->Nodes.Num() == 0)
	{
		_targetPath->Nodes.Add(location);
		_currentNode = &_targetPath->Nodes.Last();

		return;
	}
	
	const int nearestIndex = FindNearestPoint(location);

	if (nearestIndex == _targetPath->Nodes.Num() - 1)
	{
		_targetPath->Nodes.Add(location);
		_currentNode = &_targetPath->Nodes.Last(); 

		return;
	}
            
	_targetPath->Nodes.Insert(location, nearestIndex + 1);
	_currentNode = &_targetPath->Nodes[nearestIndex + 1];
}

void FPIPathMakerEditor::GrabNearestVector(FVector location)
{
	if (_targetPath == nullptr) return;
	if (_targetPath->Nodes.Num() == 0) return;

	const int nearestIndex = FindNearestPoint(location);

	if (nearestIndex < 0 || nearestIndex >= _targetPath->Nodes.Num()) return;

	_currentNode = &_targetPath->Nodes[nearestIndex];
}

void FPIPathMakerEditor::DeleteNearestVector(FVector location) const
{
	if (_currentNode != nullptr) return;

	const int nearestIndex = FindNearestPoint(location);
            
	if (nearestIndex < 0 || nearestIndex >= _targetPath->Nodes.Num()) return;

	_targetPath->Nodes.RemoveAt(nearestIndex);
	_targetPath->MarkPackageDirty();
}

void FPIPathMakerEditor::FinishPlacingNode()
{
	_currentNode = nullptr;
	_targetPath->MarkPackageDirty();
}

void FPIPathMakerEditor::MarkDirtyAndSave() const
{
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
}

void FPIPathMakerEditor::Exit()
{
	FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
	Toolkit.Reset();

	FEdMode::Exit();
}

void FPIPathMakerEditor::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	
}

bool FPIPathMakerEditor::InputKey(FEditorViewportClient* ViewportClient,
                                  FViewport* Viewport, FKey Key, EInputEvent Event)
{
	if (_targetPath == nullptr) return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);

	if (Event == IE_Pressed && !Key.IsMouseButton())
	{
		const FViewportCursorLocation& location = ViewportClient->GetCursorWorldLocationFromMousePos();
		const FVector& mouseLocation = GetWorldPosition(location);
		
		if (Key == EKeys::N) // new
		{
			CreateNewNode(mouseLocation);
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

		if(Key == EKeys::S)
		{
			MarkDirtyAndSave();
			return true;
		}
	}
	
	return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);
}

void FPIPathMakerEditor::SetEditingPath(UPIPathData* pathData)
{
	_targetPath = pathData;
}
