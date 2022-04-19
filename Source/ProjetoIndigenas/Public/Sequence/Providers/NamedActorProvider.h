#pragma once

#include "CoreMinimal.h"
#include "ActorProviderBase.h"
#include "Sequence/Sequence.h"
#include "NamedActorProvider.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UNamedActorProvider : public UActorProviderBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UObject> _owner;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<USequenceSubsystem> _subsystem;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FName ActorName;
	
	virtual AActor* GetActor() const override;
};
