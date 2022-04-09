#pragma once

#include "CoreMinimal.h"
#include "PIActor.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APIActor : public AActor
{
	GENERATED_BODY()
	
#if WITH_EDITOR
public:
	virtual void DrawVisualization(FPrimitiveDrawInterface* PDI) { }
#endif
};
