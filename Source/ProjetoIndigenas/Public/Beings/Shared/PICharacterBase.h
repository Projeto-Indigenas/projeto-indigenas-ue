#pragma once

#include "CoreMinimal.h"
#include "Actions/PIActionBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Beings/Shared/States/PIStateBase.h"
#include "PICharacterBase.generated.h"

class FPIInputDelegates;
class FPIStateBase;
class UPIAnimInstanceBase;
class APIClimbableTree;
class FPIMovementState;
class FPIClimbingState;

UCLASS()
class PROJETOINDIGENAS_API APICharacterBase : public ACharacter
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<FPIMovementState> _movementState;
	TSharedPtr<FPIClimbingState> _climbingState;
	
	TSharedPtr<FPIStateBase> _currentState;
	FPIActionBase* _availableAction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _rotationAcceleration = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _capsuleRadiusAcceleration = 1.f;

	void SetCurrentState(const TSharedPtr<FPIStateBase>& state);

	virtual void BeginPlay() override;
	
	void CreateMovementState(const float& capsuleRadius, const float& movementAcceleration);
	void CreateClimbingState(const float& capsuleRadius, const float& movementAcceleration);

public:
	TUniquePtr<FPIInputDelegates> InputDelegates;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetInputX(float x) { }
	virtual void SetInputY(float y) { }
	virtual void ToggleRun() { }
	virtual void Dodge() { }
	virtual void SetDirectionYaw(float yaw) { }
	virtual void StartClimbing(APIClimbableTree* tree) { }
	virtual void StopClimbing(APIClimbableTree* tree) { }

	void SetAvailableAction(FPIActionBase* action);

#pragma region Templates Declarations
	template<typename TAnimInstance> TAnimInstance* GetAnimInstance();
	template<typename TComponent> TComponent* GetComponent();
#pragma endregion Templates Declarations
};

#pragma region Templates Implementations
template <typename TAnimInstance>
TAnimInstance* APICharacterBase::GetAnimInstance()
{
	return Cast<TAnimInstance>(GetMesh()->GetAnimInstance());
}

template <typename TComponent>
TComponent* APICharacterBase::GetComponent()
{
	UActorComponent* component = GetComponentByClass(TComponent::StaticClass());
	return Cast<TComponent>(component);
}
#pragma endregion Templates Implementations
