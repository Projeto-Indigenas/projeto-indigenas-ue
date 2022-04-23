#pragma once

#include "CoreMinimal.h"
#include "PISequenceStepBase.h"
#include "Beings/NPC/PINpcCharacter.h"
#include "PISequenceStepTargetActorBase.generated.h"

DECLARE_DYNAMIC_DELEGATE_RetVal(AActor*, FPISequenceStepActorProviderDelegate);

UCLASS(Abstract, BlueprintType)
class PROJETOINDIGENAS_API UPISequenceStepTargetActorBase : public UPISequenceStepBase
{
	GENERATED_BODY()

	TWeakObjectPtr<AActor> _targetActor;

protected:
	UPROPERTY(BlueprintReadWrite)
	FPISequenceStepActorProviderDelegate _targetActorProviderDelegate;

	template<typename TActorType>
	TActorType* GetTargetActor()
	{
		return Cast<TActorType>(_targetActor.Get());
	}

public:
	virtual void BeginPlay(UGameInstance* gameInstance) override;
};
