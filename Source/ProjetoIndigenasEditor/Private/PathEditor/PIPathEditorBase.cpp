#include "PathEditor/PIPathEditorBase.h"

#include <SEditorViewport.h>

int FPIPathEditorBase::FindNearestVector(const FVector& location) const
{
	FVector nearestLocation = FVector::ZeroVector;
	
	const TArray<FVector>& nodes = GetNodes();
	
	int nearestIndex = -1;
	for (int index = 0; index < nodes.Num(); ++index)
	{
		const FVector& currentLocation = nodes[index];
		if (FVector::Distance(currentLocation, location) < FVector::Distance(nearestLocation, location))
		{
			nearestIndex = index;
			nearestLocation = currentLocation;
		}
	}
	
	return nearestIndex;
}

void FPIPathEditorBase::FocusNearestVector(
	FEditorViewportClient* viewportClient, 
	const FVector& mouseLocation) const
{
	const int& nearestVector = FindNearestVector(mouseLocation);

	const TArray<FVector>& nodes = GetNodes();
	
	if (nearestVector < 0 || nearestVector >= nodes.Num()) return;

	const FVector& targetLocation = nodes[nearestVector];

	const TWeakPtr<SEditorViewport> editorViewport = viewportClient->GetEditorViewportWidget();
	FViewportCameraTransform& transform = viewportClient->ViewTransformPerspective;

	constexpr float distance = -100.f;
	const FVector cameraOffsetVector = transform.GetRotation().Vector() * distance;

	transform.SetLookAt(targetLocation);
	transform.TransitionToLocation(targetLocation + cameraOffsetVector, editorViewport, false);
}

void FPIPathEditorBase::CreateNewVector(const FVector& location)
{
	if (_currentNode != nullptr) return;

	TArray<FVector>& nodes = GetNodes();
	
	if (nodes.Num() == 0)
	{
		nodes.Add(location);
		_currentNode = &nodes.Last();
		_currentNodeIndex = nodes.Num() - 1;

		return;
	}

	MakeInfoText(TEXT("Create new node"));
	
	const int nearestIndex = FindNearestVector(location);

	if (nearestIndex == nodes.Num() - 1)
	{
		nodes.Add(location);
		_currentNode = &nodes.Last();
		_currentNodeIndex = nodes.Num() - 1;

		return;
	}

	const int insertIndex = nearestIndex + 1;
	nodes.Insert(location, insertIndex);
	_currentNode = &nodes[insertIndex];
	_currentNodeIndex = insertIndex;
}

void FPIPathEditorBase::GrabNearestVector(const FVector& location)
{
	TArray<FVector>& nodes = GetNodes();
	
	if (nodes.Num() == 0) return;

	const int nearestIndex = FindNearestVector(location);

	if (nearestIndex < 0 || nearestIndex >= nodes.Num()) return;

	MakeInfoText(TEXT("Grabing nearest vector"));

	_currentNode = &nodes[nearestIndex];
	_currentNodeIndex = nearestIndex;
}

void FPIPathEditorBase::DeleteNearestVector(const FVector& location)
{
	TArray<FVector>& nodes = GetNodes();
	
	if (_currentNodeIndex != -1)
	{
		nodes.RemoveAt(_currentNodeIndex);
		MarkDirty();
		
		return;
	}

	const int nearestIndex = FindNearestVector(location);
            
	if (nearestIndex < 0 || nearestIndex >= nodes.Num()) return;

	MakeInfoText(TEXT("Deleting nearest vector"));

	nodes.RemoveAt(nearestIndex);
	MarkDirty();
}

void FPIPathEditorBase::FinishPlacingNode()
{
	_currentNode = nullptr;
	_currentNodeIndex = -1;
	MarkDirty();

	MakeInfoText(TEXT("Waiting for input"));
}

void FPIPathEditorBase::Save()
{
	_currentNode = nullptr;
	_currentNodeIndex = -1;
	MarkDirty();

	MakeInfoText(TEXT("Saved path"));
}
