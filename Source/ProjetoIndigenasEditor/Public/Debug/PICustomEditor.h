#pragma once

#include "CoreMinimal.h"

class FEditorViewportClient;

class PROJETOINDIGENASEDITOR_API FPICustomEditor
{
public:
	FPICustomEditor() = default;
	virtual ~FPICustomEditor() = default;

	virtual void SetActor(AActor* actor) = 0;

	virtual bool IsEditorForClass(UClass* cls) = 0;
	
	virtual void DrawVisualization(
		FEditorViewportClient* ViewportClient,
		FPrimitiveDrawInterface* PDI) = 0;
	virtual void DrawVisualizationHUD(FCanvas* Canvas) { }
	virtual bool HandleInputKey(
		FEditorViewportClient* ViewportClient,
		const FKey& Key,
		const EInputEvent& Event) { return false; }
};
