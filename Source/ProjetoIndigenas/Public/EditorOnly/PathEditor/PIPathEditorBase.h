#pragma once

#include "CoreMinimal.h"

class PROJETOINDIGENAS_API IPIPathEditorDataProvider
{
	TArray<FVector> _nodes;
	FString _pathName;
	
public:
	IPIPathEditorDataProvider() = default;
	virtual ~IPIPathEditorDataProvider() = default;
	
	virtual TArray<FVector>& GetNodes() = 0;
};

class PROJETOINDIGENAS_API FPIPathEditorBase
{
	IPIPathEditorDataProvider* _dataProvider = nullptr;
	FVector* _currentNode = nullptr;
	int _currentNodeIndex = -1;
	
protected:
	virtual int FindNearestVector(const FVector& location) const;
	virtual void CreateNewVector(const FVector& location);
	virtual void GrabNearestVector(const FVector& location);
	virtual void DeleteNearestVector(const FVector& location);
	virtual void FinishPlacingNode();
	virtual void Save();

	FORCEINLINE FVector* GetCurrentNode() const { return _currentNode; }
	FORCEINLINE void SetCurrentNodeValue(const FVector& vector) const { *_currentNode = vector; }
	FORCEINLINE IPIPathEditorDataProvider* GetDataProvider() const { return _dataProvider; }

	virtual void MakeInfoText(const TCHAR* infoText) { }
	virtual void MarkDirty() { }

public:
	FPIPathEditorBase() = default;
	virtual ~FPIPathEditorBase() = default;

	virtual void SetDataProvider(IPIPathEditorDataProvider* dataProvider);
};
