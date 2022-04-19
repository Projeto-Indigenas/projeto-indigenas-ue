#include "Sequence/Providers/NamedActorProvider.h"

#include "Sequence/SequenceSubsystem.h"

void UNamedActorProvider::BeginPlay()
{
	_subsystem = USequenceSubsystem::GetSequenceSubsystem(this);
}

AActor* UNamedActorProvider::GetActor() const
{
	if (!_subsystem.IsValid()) return nullptr;
	return _subsystem->GetActor<AActor>(GetOuter(), ActorName);
}
