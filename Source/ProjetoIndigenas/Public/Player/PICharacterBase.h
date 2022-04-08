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

protected:
	FAcceleratedVector _characterRotator;
	
	FVector _inputVector;
	float _directionYaw;
	bool _run;
	bool _canStartClimbingTree;

	void UpdateMovementSpeed();

	template<typename TAnimInstance>
	TAnimInstance* GetAnimInstance() { return Cast<TAnimInstance>(_animInstance.Get()); }
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationAcceleration = 1.f;
	
	virtual void Tick(float DeltaSeconds) override;

	void SetXInput(float x);
	void SetYInput(float y);
	void SetDirectionYaw(const float& directionYaw);
	void Dodge();
	void ToggleRun();
	virtual void StartClimbing();
	virtual void StopClimbing();

	void SetCanStartClimbingTree(bool canStartClimbing);
};
