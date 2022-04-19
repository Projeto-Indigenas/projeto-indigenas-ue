#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.h"
#include "NamedActorProvider.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UNamedActorProvider : public UActorProviderBase
{
	GENERATED_BODY()

	TWeakObjectPtr<USequenceSubsystem> _subsystem;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	FName ActorName;

	virtual void BeginPlay() override;
	
	virtual AActor* GetActor() const override;
};
