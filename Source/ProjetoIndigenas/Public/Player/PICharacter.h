#pragma once

#include "CoreMinimal.h"
#include "PICameraController.h"
#include "PICharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public ACharacter
{
	GENERATED_BODY()

	TWeakObjectPtr<UPICharacterAnimInstance> _animInstance;
	TWeakObjectPtr<APICameraController> _cameraController;
	
	FVector _inputVector;
	FRotator _characterRotator;
	bool _run;
	
	void MoveXInputBinding(float value);
	void MoveYInputBinding(float value);
	void RunInputBinding();
	void UpdateMovementSpeed();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Velocity = 100.f;
	
public:
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetCameraController(APICameraController* cameraController);
};
