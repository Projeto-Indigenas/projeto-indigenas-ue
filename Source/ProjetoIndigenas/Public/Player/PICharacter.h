#pragma once

#include "CoreMinimal.h"
#include "PICameraController.h"
#include "PICharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "Misc/Vectors.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public ACharacter
{
	GENERATED_BODY()

	TWeakObjectPtr<UPICharacterAnimInstance> _animInstance;
	TWeakObjectPtr<APICameraController> _cameraController;
	
	FVector _inputVector;
	FAcceleratedVector _characterRotator;
	bool _run;
	
	void MoveXInputBinding(float value);
	void MoveYInputBinding(float value);
	void RunInputBinding();
	void DodgeInputBinding();
	void UpdateMovementSpeed();
	
public:
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationAcceleration = 1.f;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetCameraController(APICameraController* cameraController);
};
