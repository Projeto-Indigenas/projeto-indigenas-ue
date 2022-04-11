#include "EditorOnly/PathEditor/PIPathEditorBase.h"

int FPIPathEditorBase::FindNearestVector(const FVector& location) const
{
	FVector nearestLocation = FVector::ZeroVector;
	
	const TArray<FVector>& nodes = _dataProvider->GetNodes();
	
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

void FPIPathEditorBase::CreateNewVector(const FVector& location)
{
	if (_currentNode != nullptr) return;

	TArray<FVector>& nodes = _dataProvider->GetNodes();
	
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
	if (_dataProvider == nullptr) return;

	TArray<FVector>& nodes = _dataProvider->GetNodes();
	
	if (nodes.Num() == 0) return;

	const int nearestIndex = FindNearestVector(location);

	if (nearestIndex < 0 || nearestIndex >= nodes.Num()) return;

	MakeInfoText(TEXT("Grabing nearest vector"));

	_currentNode = &nodes[nearestIndex];
	_currentNodeIndex = nearestIndex;
}

void FPIPathEditorBase::DeleteNearestVector(const FVector& location)
{
	TArray<FVector>& nodes = _dataProvider->GetNodes();
	
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

void FPIPathEditorBase::SetDataProvider(IPIPathEditorDataProvider* dataProvider)
{
	_dataProvider = dataProvider;
}
