#include "Sequence/Providers/NamedActorProvider.h"

#include "Sequence/SequenceSubsystem.h"

AActor* UNamedActorProvider::GetActor() const
{
	if (!_subsystem.IsValid()) return nullptr;
	return _subsystem->GetActor<AActor>(_owner.Get(), ActorName);
}
