#pragma once

#include "UnrealEd.h"
#include "NPC/Paths/PIPathData.h"

class FPIPathMakerEditor : public FEdMode
{
	UPIPathData* _targetPath = nullptr;
	FVector* _currentNode = nullptr;

	static FVector GetWorldPosition(const FViewportCursorLocation& mouseLocation);
	int FindNearestPoint(FVector location) const;
	void CreateNewNode(FVector location);
	void GrabNearestVector(FVector location);
	void DeleteNearestVector(FVector location) const;
	void FinishPlacingNode();
	void MarkDirtyAndSave() const;
	
public:
	const static FEditorModeID EditorModeID;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;

	void SetEditingPath(UPIPathData* pathData);
};
