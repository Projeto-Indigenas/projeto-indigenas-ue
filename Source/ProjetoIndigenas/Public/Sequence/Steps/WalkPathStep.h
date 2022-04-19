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

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UWalkPathStep : public USequenceStep, public ISequenceStepExecutor
{
	GENERATED_BODY()

	TWeakObjectPtr<APINpcController> _targetController;
	TWeakObjectPtr<APINpcCharacter> _targetCharacter;

	TUniquePtr<FPIDestinationController> _destinationController;

	void MoveToNextNode();
	void PathRequestCompleted(FAIRequestID requestId, const FPathFollowingResult& result);
	
protected:
	UPROPERTY(BlueprintReadOnly, Instanced, meta = (ExposeOnSpawn))
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	UPIPathData* _pathData;

	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	bool _cycleDestinations = false;
	
	virtual void ExecuteStep() override;
	virtual void Finish() override;
	
public:
	virtual void BeginPlay(UGameInstance* gameInstance) override;

	virtual void BeginExecution() override;
	virtual void Tick(float deltaTime) override;
};
