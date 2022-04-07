#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Sequence/SequenceStep.h"
#include "SpawnActorStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API USpawnActorStep : public USequenceStep
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FName ActorName;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool SpawnController;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TWeakObjectPtr<APlayerStart> ActorPlayerStart;

	virtual void ExecuteStep(const FSequenceQuery& sequenceQuery) override;
};
