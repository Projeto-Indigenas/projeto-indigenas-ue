#include "SavedData/PISaveGameSubsystem.h"

#include <Kismet/GameplayStatics.h>

#include "Misc/Logging.h"
#include "SavedData/PISaveGameData.h"

template<typename TSaveGameClass>
bool UPISaveGameSubsystem::SaveGameInternal(TSaveGameClass* saveGame)
{
	const FString& slotName = TSaveGameClass::StaticClass()->GetName();
	return UGameplayStatics::SaveGameToSlot(saveGame, slotName, 0);
}

template<typename TSaveGameClass>
TSaveGameClass* UPISaveGameSubsystem::LoadGameInternal()
{
	const FString& slotName = TSaveGameClass::StaticClass()->GetName();
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot(slotName, 0);
	return Cast<TSaveGameClass>(saveGame);
}

template <typename TSaveGameClass>
bool UPISaveGameSubsystem::HasSavedGameInternal()
{
	const FString& slotName = TSaveGameClass::StaticClass()->GetName();
	return UGameplayStatics::DoesSaveGameExist(slotName, 0);
}

UPISaveGameSubsystem* UPISaveGameSubsystem::GetSaveGameSubsystem(const UObject* worldContextObject)
{
	return worldContextObject->GetWorld()->GetGameInstance()->GetSubsystem<UPISaveGameSubsystem>();
}

void UPISaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (HasSavedGameInternal<UPISaveGameData>())
	{
		_savedGameData = TStrongObjectPtr(LoadGameInternal<UPISaveGameData>());
		PlayerCharacterData = _savedGameData->PlayerCharacterSavedData;
	}
	else
	{
		_savedGameData = TStrongObjectPtr(NewObject<UPISaveGameData>());
	}
}

void UPISaveGameSubsystem::SaveGame()
{
	_savedGameData->PlayerCharacterSavedData = PlayerCharacterData;
	
	if (SaveGameInternal(_savedGameData.Get())) return;
	
	PI_LOGV_UOBJECT(Error, TEXT("Failed trying to save game data"))
}

void UPISaveGameSubsystem::LoadGame()
{
	if (HasSavedGame())
	{
		_savedGameData = TStrongObjectPtr(LoadGameInternal<UPISaveGameData>());
	}
}

bool UPISaveGameSubsystem::HasSavedGame()
{
	return HasSavedGameInternal<UPISaveGameData>();
}

// template instantiation
template bool UPISaveGameSubsystem::SaveGameInternal(UPISaveGameData*);
template UPISaveGameData* UPISaveGameSubsystem::LoadGameInternal();
template bool UPISaveGameSubsystem::HasSavedGameInternal<UPISaveGameData>();

