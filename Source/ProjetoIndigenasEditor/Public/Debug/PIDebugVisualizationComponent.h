#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "PIDebugVisualizationComponent.generated.h"

class FPICustomEditor;

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class PROJETOINDIGENASEDITOR_API UPIDebugVisualizationComponent : public UActorComponent
{
	GENERATED_BODY()

	TSharedPtr<FPICustomEditor> _customEditor;

protected:
	virtual void OnRegister() override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ShowOnlyWhenSelected = true;
	
	UPIDebugVisualizationComponent();
	
	void DrawVisualization(FPrimitiveDrawInterface* PDI) const;
	void DrawVisualizationHUD(FCanvas* Canvas) const;
};
