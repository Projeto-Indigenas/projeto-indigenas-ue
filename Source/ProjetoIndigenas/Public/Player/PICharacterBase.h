#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Interactables/PIClimbableTree.h"
#include "States/PIStateBase.h"
#include "PICharacterBase.generated.h"

class FPIStateBase;
class UPIAnimInstanceBase;

UCLASS()
class PROJETOINDIGENAS_API APICharacterBase : public ACharacter
{
	GENERATED_BODY()

protected:
	TSharedPtr<FPIStateBase> _currentState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _rotationAcceleration = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _capsuleRadiusAcceleration = 1.f;

	void SetCurrentState(const TSharedPtr<FPIStateBase>& state);

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetInputX(float x) { }
	virtual void SetInputY(float y) { }
	virtual void ToggleRun() { }
	virtual void Dodge() { }
	virtual void SetDirectionYaw(float yaw) { }
	virtual void StartClimbing() { }
	virtual void StopClimbing() { }

	virtual void SetClimbableTree(APIClimbableTree* tree) { }

#pragma region Templates Declarations
	template<typename TAnimInstance> TAnimInstance* GetAnimInstance();
	template<typename TComponent> TComponent* GetComponent();
#pragma endregion Templates Declarations
};

#pragma region Templates Implementations
template <typename TAnimInstance>
TAnimInstance* APICharacterBase::GetAnimInstance()
{
	return Cast<TAnimInstance>(_currentState->GetAnimInstance());
}

template <typename TComponent>
TComponent* APICharacterBase::GetComponent()
{
	UActorComponent* component = GetComponentByClass(TComponent::StaticClass());
	return Cast<TComponent>(component);
}
#pragma endregion Templates Implementations
