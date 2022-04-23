#pragma once

#include "CoreMinimal.h"
#include "Beings/NPC/PINpcCharacter.h"
#include "Beings/NPC/PINpcController.h"
#include "Beings/NPC/Paths/PIDestinationController.h"
#include "Beings/NPC/Paths/PIPathData.h"
#include "Sequence/PISequenceStep.h"
#include "Sequence/PISequenceStepExecutor.h"
#include "PIWalkPathStep.generated.h"

UCLASS(BlueprintType)
class PROJETOINDIGENAS_API UPIWalkPathStep : public UPISequenceStep, public IPISequenceStepExecutor
{
	GENERATED_BODY()

	TWeakObjectPtr<APINpcController> _targetController;
	
	TUniquePtr<FPIDestinationController> _destinationController;

	void MoveToNextNode();
	void PathRequestCompleted(FAIRequestID requestId, const FPathFollowingResult& result);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn))
	TWeakObjectPtr<APINpcCharacter> _targetCharacter;
	
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
