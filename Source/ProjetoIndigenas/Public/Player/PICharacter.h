#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Misc/Vectors.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public ACharacter
{
	GENERATED_BODY()

	TWeakObjectPtr<UPIAnimInstanceBase> _animInstance;
	FAcceleratedVector _characterRotator;
	
	FVector _inputVector;
	float _directionYaw;
	bool _run;

	void UpdateMovementSpeed();
	
public:
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationAcceleration = 1.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetXInput(float x);
	void SetYInput(float y);
	void SetDirectionYaw(const float& directionYaw);
	void Dodge();
	void ToggleRun();
};
