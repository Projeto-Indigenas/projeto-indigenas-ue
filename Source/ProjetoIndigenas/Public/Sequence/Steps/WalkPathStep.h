﻿#pragma once

#include "CoreMinimal.h"
#include "NPC/PINpcCharacter.h"
#include "NPC/PINpcController.h"
#include "NPC/Paths/PIPathData.h"
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
	
protected:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Instanced)
	UActorProviderBase* _actorProvider;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	UPIPathData* _pathData;
	
	virtual void ExecuteStep(const FSequenceQuery& sequenceQuery) override;
	
public:
	virtual void BeginPlay(UGameInstance* gameInstance) override;

	virtual void BeginExecution() override;
	virtual void Tick(float deltaTime) override;
};
