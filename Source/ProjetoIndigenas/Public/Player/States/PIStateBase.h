#pragma once

#include "CoreMinimal.h"
#include "Player/PIAnimInstanceBase.h"
#include "Player/PICharacterBase.h"
#include "Player/Input/PIInputDelegates.h"

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

	virtual void Enter(FPIInputDelegates& inputDelegates) { }
	virtual void Exit(FPIInputDelegates& inputDelegates) { }
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
