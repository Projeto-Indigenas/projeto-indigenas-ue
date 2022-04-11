#pragma once

#include "CoreMinimal.h"
#include "Debug/PICustomEditor.h"
#include "Interactables/PIClimbableTree.h"
#include "PathEditor/PIPathEditorBase.h"

class PROJETOINDIGENASEDITOR_API FPIClimbableTreeCustomEditor : public FPICustomEditor, public FPIPathEditorBase
{
	TWeakObjectPtr<APIClimbableTree> _climbableTree;

	static bool TryGetTargetLocation(const UWorld* world, const FViewportCursorLocation& mouseLocation, FVector& outLocation);
	
public:
	FPIClimbableTreeCustomEditor() = default;

	virtual void SetActor(AActor* actor) override;
	virtual bool IsEditorForClass(UClass* cls) override;

	virtual TArray<FVector>& GetNodes() const override;

	virtual void DrawVisualization(FEditorViewportClient* ViewportClient, FPrimitiveDrawInterface* PDI) override;
	virtual void DrawVisualizationHUD(FCanvas* Canvas) override;
	virtual bool HandleInputKey(
		FEditorViewportClient* ViewportClient,
		const FKey& Key,
		const EInputEvent& Event) override;

	virtual void MarkDirty() override;
	virtual void Save() override;
};
