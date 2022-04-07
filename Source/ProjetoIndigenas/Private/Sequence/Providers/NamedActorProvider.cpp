#include "Sequence/Providers/NamedActorProvider.h"

AActor* UNamedActorProvider::GetActor(const FSequenceQuery* sequenceQuery) const
{
	return sequenceQuery->FindActor(ActorName);
}
