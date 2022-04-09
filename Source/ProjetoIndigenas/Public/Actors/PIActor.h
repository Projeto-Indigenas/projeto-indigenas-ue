#pragma once

#include "CoreMinimal.h"
#include "PIActor.generated.h"

class FPICustomEditor;

UCLASS()
class PROJETOINDIGENAS_API APIActor : public AActor
{
	GENERATED_BODY()
	
#if WITH_EDITOR
public:
	virtual TSharedPtr<FPICustomEditor> GetCustomEditor() { return nullptr; }
#endif
};
