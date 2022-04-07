#pragma once

#include "CoreMinimal.h"
#include "Sequence/Sequence.h"
#include "ActorProviderBase.generated.h"

struct FSequenceQuery;

UCLASS(Abstract, EditInlineNew)
class PROJETOINDIGENAS_API UActorProviderBase : public UObject
{
	GENERATED_BODY()

protected:
	virtual AActor* GetActor(const FSequenceQuery& sequenceQuery) const { return nullptr; }
	
public:
	template<typename TActor>
	TActor* GetActor(const FSequenceQuery& sequenceQuery) const
	{
		return Cast<TActor>(GetActor(sequenceQuery));
	}
};
