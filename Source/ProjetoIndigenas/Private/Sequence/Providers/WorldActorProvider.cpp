#include "Sequence/Providers/WorldActorProvider.h"

AActor* UWorldActorProvider::GetActor(const FSequenceQuery& sequenceQuery) const
{
	return _worldActor.Get();
}
