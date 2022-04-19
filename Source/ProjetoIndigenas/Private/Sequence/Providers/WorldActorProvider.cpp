#include "Sequence/Providers/WorldActorProvider.h"

AActor* UWorldActorProvider::GetActor() const
{
	return _worldActor.Get();
}
