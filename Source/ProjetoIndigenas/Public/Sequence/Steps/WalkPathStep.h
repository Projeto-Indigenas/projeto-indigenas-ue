#pragma once

#include "CoreMinimal.h"
#include "Beings/NPC/PINpcCharacter.h"
#include "Beings/NPC/PINpcController.h"
#include "Beings/NPC/Paths/PIDestinationController.h"
#include "Beings/NPC/Paths/PIPathData.h"
#include "Sequence/SequenceStep.h"
#include "Sequence/SequenceStepExecutor.h"
#include "Sequence/Providers/ActorProviderBase.h"
#include "WalkPathStep.generated.h"

UCLASS()
class PROJETOINDIGENAS_API UWalkPathStep : public USequenceStep, public ISequenceStepExecutor
{
	GENERATED_BODY()

	TWeakObjectPtr<APINpcController> _targetController;
	TWeakObjectPtr<APINpcCharacter> _targetCharacter;

	TUniquePtr<FPIDestinationController> _destinationController;

	void MoveToNextNode();
	void PathRequestCompleted(FAIRequestID requestId, const FPathFollowingResult& result);
	
protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Instanced)
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPIPathData* _pathData;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	bool _cycleDestinations = false;
	
	virtual void ExecuteStep(const FSequenceQuery* sequenceQuery) override;
	virtual void Finish() override;
	
public:
	virtual void BeginPlay(UGameInstance* gameInstance) override;

	virtual void BeginExecution() override;
	virtual void Tick(float deltaTime) override;
};
