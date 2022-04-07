#pragma once

#include "CoreMinimal.h"

class FEditorViewportClient;

class PROJETOINDIGENASEDITOR_API FPIPathEditorBase
{
	FVector* _currentNode = nullptr;
	int _currentNodeIndex = -1;
	
protected:
	virtual int FindNearestVector(const FVector& location) const;
	void FocusNearestVector(
		FEditorViewportClient * viewportClient,
		const FVector& location);
	virtual void CreateNewVector(const FVector& location);
	virtual void GrabNearestVector(const FVector& location);
	virtual void DeleteNearestVector(const FVector& location);
	virtual void FinishPlacingNode();
	virtual void Save();

	FORCEINLINE FVector* GetCurrentNode() const { return _currentNode; }
	FORCEINLINE void SetCurrentNodeValue(const FVector& vector) const { *_currentNode = vector; }

	virtual void MakeInfoText(const TCHAR* infoText) { }
	virtual void MarkDirty() { }
	virtual TArray<FVector>& GetNodes() const = 0;

	virtual FVector GetWorldVector(FVector vector) { return vector; }
	virtual FVector GetLocalVector(FVector vector) { return vector; }

public:
	FPIPathEditorBase() = default;
	virtual ~FPIPathEditorBase() = default;
};
