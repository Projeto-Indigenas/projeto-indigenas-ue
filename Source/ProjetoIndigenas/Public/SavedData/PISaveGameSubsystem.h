#pragma once

#include "CoreMinimal.h"
#include "PISaveGameData.h"
#include "PISaveGameSubsystem.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	TStrongObjectPtr<UPISaveGameData> _savedGameData; 
	
	static bool SaveGameInternal(USaveGame* saveGame);
	template<typename TSaveGameClass> static TSaveGameClass* LoadGameInternal();
	template<typename TSaveGameClass> static bool HasSavedGameInternal();
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintPure)
	FPIPlayerCharacterSavedData& GetPlayerCharacterSavedData() const;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintPure)
	bool HasSavedGame();
};
