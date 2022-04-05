#include "PathMaker/PIPathMakerEditor.h"

#include "PathMaker/PIPathMakerToolkit.h"
#include "Toolkits/ToolkitManager.h"

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
		_currentNodeIndex = _targetPath->Nodes.Num() - 1;

		return;
	}

	MakeInfoText(TEXT("Create new node"));
	
	const int nearestIndex = FindNearestPoint(location);

	if (nearestIndex == _targetPath->Nodes.Num() - 1)
	{
		_targetPath->Nodes.Add(location);
		_currentNode = &_targetPath->Nodes.Last();
		_currentNodeIndex = _targetPath->Nodes.Num() - 1;

		return;
	}

	const int insertIndex = nearestIndex + 1;
	_targetPath->Nodes.Insert(location, insertIndex);
	_currentNode = &_targetPath->Nodes[insertIndex];
	_currentNodeIndex = insertIndex;
}

void FPIPathMakerEditor::GrabNearestVector(FVector location)
{
	if (_targetPath == nullptr) return;
	if (_targetPath->Nodes.Num() == 0) return;

	const int nearestIndex = FindNearestPoint(location);

	if (nearestIndex < 0 || nearestIndex >= _targetPath->Nodes.Num()) return;

	MakeInfoText(TEXT("Grabing nearest vector"));

	_currentNode = &_targetPath->Nodes[nearestIndex];
	_currentNodeIndex = nearestIndex;
}

void FPIPathMakerEditor::DeleteNearestVector(FVector location) const
{
	if (_currentNodeIndex != -1)
	{
		_targetPath->Nodes.RemoveAt(_currentNodeIndex);
		_targetPath->MarkPackageDirty();
		
		return;
	}

	const int nearestIndex = FindNearestPoint(location);
            
	if (nearestIndex < 0 || nearestIndex >= _targetPath->Nodes.Num()) return;

	MakeInfoText(TEXT("Deleting nearest vector"));

	_targetPath->Nodes.RemoveAt(nearestIndex);
	_targetPath->MarkPackageDirty();
}

void FPIPathMakerEditor::FinishPlacingNode()
{
	_currentNode = nullptr;
	_currentNodeIndex = -1;
	_targetPath->MarkPackageDirty();

	MakeInfoText(TEXT("Waiting for input"));
}

void FPIPathMakerEditor::MarkDirtyAndSave()
{
	_currentNode = nullptr;
	_currentNodeIndex = -1;
	_targetPath->MarkPackageDirty();
	
	TArray<UPackage*> toSave;
	toSave.Add(_targetPath->GetPackage());
	UEditorLoadingAndSavingUtils::SavePackages(toSave, true);

	SetEditingPath(nullptr);

	MakeInfoText(TEXT("Saved path"));
}

void FPIPathMakerEditor::MakeInfoText(FString currentState) const
{
	if (Toolkit == nullptr) return;

	const FString& vectorText = _currentNode ? FString::Printf(TEXT(
		"\n"
		"\tX: %.2f\n"
		"\tY: %.2f\n"
		"\tZ: %.2f"
	), _currentNode->X, _currentNode->Y, _currentNode->Z) : FString();
	
	const FString& infoText = FString::Printf(TEXT(
		"Current node count: %d\n"
		"Current state: %s\n"
		"Current editing node: %s"),
		_targetPath ? _targetPath->Nodes.Num() : 0,
		*currentState,
		*vectorText);

	static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetInfoText(infoText);
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

	if (_currentNode == nullptr) return;

	const FViewportCursorLocation& mouseLocation = ViewportClient->GetCursorWorldLocationFromMousePos();
	const FVector& worldLocation = GetWorldLocation(ViewportClient->GetWorld(), mouseLocation);
	
	*_currentNode = worldLocation;
	
	MakeInfoText(TEXT("Placing node"));
}

void FPIPathMakerEditor::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);

	if (_targetPath == nullptr) return;

	constexpr ESceneDepthPriorityGroup depthPriority = SDPG_Foreground;

	const int& nodesCount = _targetPath->Nodes.Num();
	const FMaterialRenderProxy* materialRenderProxy = GEngine->VertexColorMaterial->GetRenderProxy();
	
	for (int index = 0; index < nodesCount; ++index)
	{
		const FVector& current = _targetPath->Nodes[index];

		if (index < nodesCount - 1)
		{
			const FVector& next = _targetPath->Nodes[index + 1];

			PDI->DrawPoint(current, FColor::Blue, 10.f, depthPriority);
			PDI->DrawLine(current, next, FLinearColor::Red, depthPriority, 1.f);
			

			const FVector& direction = next - current;
			const float& distance = FVector::Distance(next, current);
			const float& length = distance * .2f;
			const float& arrowSize = length * .1f;
			const FMatrix matrix = FLookFromMatrix(current, direction, FVector::UpVector).GetMatrixWithoutScale();
			DrawDirectionalArrow(PDI, matrix, FLinearColor::Green, length, arrowSize, depthPriority);

			continue;
		}

		PDI->DrawPoint(current, FColor::Red, 20.f, depthPriority);
	}
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

	if (pathData == nullptr)
	{
		MakeInfoText(TEXT("Waiting for path"));

		static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetObjectPath(FString());

		return;
	}

	MakeInfoText(TEXT("Waiting for input"));
	static_cast<FPIPathMakerToolkit*>(Toolkit.Get())->SetObjectPath(pathData->GetPathName());
}
