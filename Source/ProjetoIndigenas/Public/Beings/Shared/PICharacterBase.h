#pragma once

#include "CoreMinimal.h"
#include "Actions/PIActionBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Beings/Shared/States/PIStateBase.h"
#include "States/PISwimmingState.h"
#include "PICharacterBase.generated.h"

class FPIInputDelegates;
class FPIStateBase;
class UPIAnimInstanceBase;
class APIClimbableTree;
class FPIMovementState;
class FPIClimbingState;
class AWaterBody;

UCLASS()
class PROJETOINDIGENAS_API APICharacterBase : public ACharacter
{
	GENERATED_BODY()

	TWeakObjectPtr<AWaterBody> _waterBodyActor;
	
protected:
	TSharedPtr<FPIMovementState> _movementState;
	TSharedPtr<FPIClimbingState> _climbingState;
	TSharedPtr<FPISwimmingState> _swimmingState;
	
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
	void CreateSwimmingState(const float& capsuleRadius, const float& movementAcceleration);

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
	virtual void StartSwimming(AWaterBody* waterBody) { }
	virtual void EndSwimming(AWaterBody* waterBody) { }

	void SetAvailableAction(FPIActionBase* action);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

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
