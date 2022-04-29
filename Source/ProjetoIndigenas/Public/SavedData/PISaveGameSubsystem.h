#pragma once

#include "CoreMinimal.h"
#include "PISaveGameData.h"
#include "PISaveGameSubsystem.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPISaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	TStrongObjectPtr<UPISaveGameData> _savedGameData; 
	
	template<typename TSaveGameClass> static bool SaveGameInternal(TSaveGameClass* saveGame);
	template<typename TSaveGameClass> static TSaveGameClass* LoadGameInternal();
	template<typename TSaveGameClass> static bool HasSavedGameInternal();
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FPIPlayerCharacterSavedData PlayerCharacterData;
	
	static UPISaveGameSubsystem* GetSaveGameSubsystem(const UObject* worldContextObject);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintPure)
	bool HasSavedGame();
};
