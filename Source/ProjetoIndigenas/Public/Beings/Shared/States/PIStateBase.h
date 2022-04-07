#pragma once

#include "CoreMinimal.h"
#include "Beings/Shared/PIAnimInstanceBase.h"
#include "Beings/Shared/PICharacterBase.h"
#include "Beings/Player/Input/PIInputDelegates.h"

class APICharacterBase;
class UCapsuleComponent;

DECLARE_DELEGATE(FPIStateOnExitDelegate)

class PROJETOINDIGENAS_API FPIStateBase
{
	FPIStateOnExitDelegate _onExitDelegate;
	
protected:
	TWeakObjectPtr<APICharacterBase> _character;
	TWeakObjectPtr<UCapsuleComponent> _capsuleComponent;

	void InvokeOnExitDelegate() const;

public:
	explicit FPIStateBase(APICharacterBase* character);

	virtual ~FPIStateBase() = default;

	virtual void Enter(FPIInputDelegates& inputDelegates) { }
	virtual void Exit(FPIInputDelegates& inputDelegates, FPIStateOnExitDelegate onExitDelegate = nullptr);

	virtual void Tick(float DeltaSeconds) { }
};

template <typename TAnimInstance>
class PROJETOINDIGENAS_API FPIAnimatedStateBase : public FPIStateBase
{
protected:
	TWeakObjectPtr<APICharacterBase> _character;

public:
	explicit FPIAnimatedStateBase(APICharacterBase* character);
	
	FORCEINLINE TAnimInstance* GetAnimInstance() const
	{
		if (!_character.IsValid()) return nullptr;
		if (_character->GetMesh() == nullptr) return nullptr;
		return Cast<TAnimInstance>(_character->GetMesh()->GetAnimInstance());
	}
};

template <typename TStateData>
class PROJETOINDIGENAS_API FPIStateBaseWithData : public FPIStateBase
{
protected:
	const TStateData& _stateData;

public:
	FPIStateBaseWithData(APICharacterBase* character, const TStateData& stateData);
};

template <typename TAnimInstance, typename TStateData>
class PROJETOINDIGENAS_API FPIAnimatedStateBaseWithData : public FPIAnimatedStateBase<TAnimInstance>
{
protected:
	const TStateData _stateData;
	
public:
	FPIAnimatedStateBaseWithData(APICharacterBase* character, const TStateData& stateData);
};
