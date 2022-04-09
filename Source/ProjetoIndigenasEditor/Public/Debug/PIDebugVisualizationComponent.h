#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"
#include "PIDebugVisualizationComponent.generated.h"

UCLASS(ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class PROJETOINDIGENASEDITOR_API UPIDebugVisualizationComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPIDebugVisualizationComponent();

	void DrawVisualization(FPrimitiveDrawInterface* PDI) const;
};
