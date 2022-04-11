#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "PIDebugVisualizationComponent.generated.h"

class FPICustomEditor;

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class PROJETOINDIGENASEDITOR_API UPIDebugVisualizationComponent : public UActorComponent
{
	GENERATED_BODY()

	FPICustomEditor* _customEditor;

protected:
	virtual void OnRegister() override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShowOnlyWhenSelected = true;
	
	UPIDebugVisualizationComponent();

	void EndEditing() const;
	void DrawVisualization(
		const UActorComponent* Component,
		FEditorViewportClient* ViewportClient,
		FPrimitiveDrawInterface* PDI) const;
	void DrawVisualizationHUD(FCanvas* Canvas) const;
	bool HandleInputKey(
		FEditorViewportClient* ViewportClient,
		const FKey& Key,
		const EInputEvent& Event) const;
};
