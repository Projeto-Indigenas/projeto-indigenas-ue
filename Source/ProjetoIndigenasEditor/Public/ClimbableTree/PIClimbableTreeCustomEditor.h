#pragma once

#include "CoreMinimal.h"
#include "Debug/PICustomEditor.h"
#include "Interactables/PIClimbableTree.h"

class PROJETOINDIGENASEDITOR_API FPIClimbableTreeCustomEditor : public FPICustomEditor
{
	TWeakObjectPtr<APIClimbableTree> _climbableTree;
	TWeakObjectPtr<UStaticMeshComponent> _staticMeshComponent;
	TArray<FVector> _socketsLocations;

public:
	FPIClimbableTreeCustomEditor() = default;

	virtual bool IsEditorForClass(UClass* cls) override;

	virtual void EndEditing() override;

	virtual void DrawVisualization(
		const UActorComponent* Component,
		FEditorViewportClient* ViewportClient,
		FPrimitiveDrawInterface* PDI) override;
};
