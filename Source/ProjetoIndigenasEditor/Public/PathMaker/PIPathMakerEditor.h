#pragma once

#include "UnrealEd.h"
#include "NPC/Paths/PIPathData.h"

class FPIPathMakerEditor : public FEdMode
{
	UPIPathData* _targetPath = nullptr;
	FVector* _currentNode = nullptr;
	int _currentNodeIndex = -1;

	static FVector GetWorldLocation(const UWorld* world, const FViewportCursorLocation& mouseLocation);
	int FindNearestVector(const FVector& location) const;
	void CreateNewVector(const FVector& location);
	void GrabNearestVector(const FVector& location);
	void DeleteNearestVector(const FVector& location) const;
	void FocusNearestVector(const FVector& location) const;
	void FinishPlacingNode();
	void MarkDirtyAndSave();
	void MakeInfoText(FString currentState) const;
	
public:
	const static FEditorModeID EditorModeID;

	virtual void Enter() override;
	virtual void Exit() override;
	
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;

	void SetEditingPath(UPIPathData* pathData);
};
