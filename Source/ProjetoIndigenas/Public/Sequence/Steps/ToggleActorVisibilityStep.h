#pragma once

#include "CoreMinimal.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "ToggleActorVisibilityStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UToggleActorVisibilityStep : public USequenceStep
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor> _targetActor;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Instanced)
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _visible;
	
	virtual void ExecuteStep(const FSequenceQuery& sequenceQuery) override;
};
