#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceController.h"
#include "ActorProviderBase.generated.h"

class USequenceSubsystem;

UCLASS(Abstract, EditInlineNew)
class PROJETOINDIGENAS_API UActorProviderBase : public UObject
{
	GENERATED_BODY()

protected:
	virtual AActor* GetActor() const { return nullptr; }
	
public:
	template<typename TActor>
	TActor* GetActor() const
	{
		return Cast<TActor>(GetActor());
	}
};
