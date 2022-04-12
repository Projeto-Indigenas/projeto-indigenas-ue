#pragma once

#include "CoreMinimal.h"
#include "Player/PIAnimInstanceBase.h"
#include "Player/PICharacterBase.h"

class APICharacterBase;
class UCapsuleComponent;

class PROJETOINDIGENAS_API FPIStateBase
{
protected:
	TWeakObjectPtr<APICharacterBase> _character;
	TWeakObjectPtr<UPIAnimInstanceBase> _animInstance;
	TWeakObjectPtr<UCapsuleComponent> _capsuleComponent;
	
public:
	explicit FPIStateBase(APICharacterBase* character);

	virtual ~FPIStateBase() = default;

	virtual void Enter() { }
	virtual void Exit() { }
	virtual void Tick(float DeltaSeconds) { }

	FORCEINLINE UPIAnimInstanceBase* GetAnimInstance() const { return _animInstance.Get(); }
};

template<typename TStateData>
class PROJETOINDIGENAS_API FPIStateBaseWithData : public FPIStateBase
{
protected:
	const TStateData& _stateData;

public:
	explicit FPIStateBaseWithData(APICharacterBase* character, const TStateData& stateData);
};
