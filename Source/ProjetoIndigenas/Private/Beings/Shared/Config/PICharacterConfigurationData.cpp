#include "Beings/Shared/Config/PICharacterConfigurationData.h"

void UPICharacterConfigurationData::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsSaving()) return;

	PlayerCharactersMap.Empty();
	NpcCharactersMap.Empty();

	for (const FPICharacterConfiguration& configuration : _playerConfigurations)
	{
		PlayerCharactersMap.Add(configuration.CharacterId, configuration);
	}

	for (const FPICharacterConfiguration& configuration : _npcConfigurations)
	{
		NpcCharactersMap.Add(configuration.CharacterId, configuration);
	}
}
