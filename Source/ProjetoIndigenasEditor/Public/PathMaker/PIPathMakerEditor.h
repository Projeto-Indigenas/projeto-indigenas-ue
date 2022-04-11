#pragma once

#include "UnrealEd.h"
#include "EditorOnly/PathEditor/PIPathEditorBase.h"
#include "NPC/Paths/PIPathData.h"

class PROJETOINDIGENASEDITOR_API FPIPathMakerEditor : public FEdMode, FPIPathEditorBase
{
	UPIPathData* _targetPath = nullptr;
	
	static FVector GetWorldLocation(const UWorld* world, 
		const FViewportCursorLocation& mouseLocation);
	void FocusNearestVector(FEditorViewportClient * viewportClient, const FVector & mouseLocation) const;
	virtual void MarkDirty() override;
	virtual void Save() override;

protected:
	virtual void MakeInfoText(const TCHAR* infoText) override;
	
public:
	const static FEditorModeID EditorModeID;

	virtual void Enter() override;
	virtual void Exit() override;
	
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;

	virtual void SetTargetPath(UPIPathData* targetPath);
};
