#pragma once

#include "CoreMinimal.h"
#include "PIHUDBase.h"
#include "Blueprint/UserWidget.h"
#include "PIWidgetBase.generated.h"

UCLASS(Blueprintable)
class PROJETOINDIGENAS_API UPIWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	APIHUDBase* GetHUD() const;
};
