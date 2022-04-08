#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/Vectors.h"
#include "PICharacterBase.generated.h"

class UPIAnimInstanceBase;

UCLASS()
class PROJETOINDIGENAS_API APICharacterBase : public ACharacter
{
	GENERATED_BODY()

	TWeakObjectPtr<UPIAnimInstanceBase> _animInstance;
	TWeakObjectPtr<UCapsuleComponent> _capsuleComponent;
	
	FAcceleratedVector _acceleratedCharacterDirection;
	FAcceleratedValue _acceleratedCapsuleRadius;
	FAcceleratedValue _acceleratedMovementSpeed;

	FVector _inputVector;
	bool _run;
	float _directionYaw;
	
	void UpdateMovementSpeed();

protected:
	bool _canStartClimbingTree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _defaultCapsuleRadius = 34.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _defaultMovementAcceleration = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _rotationAcceleration = 1.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _capsuleRadiusAcceleration = 1.f;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	void SetXInput(float x);
	void SetYInput(float y);
	void SetDirectionYaw(const float& directionYaw);
	void Dodge();
	void ToggleRun();
	virtual void StartClimbing();
	virtual void StopClimbing();

	FORCEINLINE void SetCanStartClimbingTree(bool canStartClimbing);
	FORCEINLINE void SetCapsuleRadius(const float* radius);
	FORCEINLINE void SetMovementAcceleration(const float* acceleration);

#pragma region Templates Declarations
	template<typename TAnimInstance> TAnimInstance* GetAnimInstance();
	template<typename TComponent> TComponent* GetComponent();
#pragma endregion Templates Declarations
};

#pragma region Templates Implementations

template <typename TAnimInstance>
TAnimInstance* APICharacterBase::GetAnimInstance()
{
	if (!_animInstance.IsValid()) return nullptr;
	return Cast<TAnimInstance>(_animInstance.Get());
}

template <typename TComponent>
TComponent* APICharacterBase::GetComponent()
{
	UActorComponent* component = GetComponentByClass(TComponent::StaticClass());
	return Cast<TComponent>(component);
}

#pragma endregion Templates Implementations
