#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public ACharacter
{
	GENERATED_BODY()

	FVector _moveVector;
	FVector _cameraVector;
	FRotator _cameraRotator;
	
	void MoveXInputBinding(float value);
	void MoveYInputBinding(float value);
	void CameraXInputBinding(float value);
	void CameraYInputBinding(float value);

	void UpdateMovementSpeed();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TWeakObjectPtr<UCameraComponent> _cameraComponent;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TWeakObjectPtr<USpringArmComponent> _springArmComponent;

public:
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CameraSpeed;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
};
