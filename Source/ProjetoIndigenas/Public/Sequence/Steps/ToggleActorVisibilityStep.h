#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "ToggleActorVisibilityStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UToggleActorVisibilityStep : public USequenceStep
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor> _targetActor;
	
protected:
	UPROPERTY(BlueprintReadOnly, Instanced, meta = (ExposeOnSpawn))
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _visible;
	
	virtual void ExecuteStep() override;
};
