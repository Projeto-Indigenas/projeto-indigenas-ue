#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.generated.h"

class USequenceSubsystem;

UCLASS(Abstract, BlueprintType, EditInlineNew)
class PROJETOINDIGENAS_API UActorProviderBase : public UObject
{
	GENERATED_BODY()

protected:
	virtual AActor* GetActor() const { return nullptr; }
	
public:
	virtual void BeginPlay() { }
	
	template<typename TActor>
	TActor* GetActor() const
	{
		return Cast<TActor>(GetActor());
	}
};
