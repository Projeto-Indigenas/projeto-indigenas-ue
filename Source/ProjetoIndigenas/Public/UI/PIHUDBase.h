#pragma once

#include "CoreMinimal.h"
#include "GameFlow/PIGameFlowSubsystem.h"
#include "GameFramework/HUD.h"
#include "PIHUDBase.generated.h"

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API APIHUDBase : public AHUD
{
	GENERATED_BODY()

	TWeakObjectPtr<UPIGameFlowSubsystem> _gameFlowSubsystem;

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void TransitionTo(const FName state);
};
