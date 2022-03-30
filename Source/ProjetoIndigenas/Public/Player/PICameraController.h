#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "PICameraController.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICameraController : public AActor
{
	GENERATED_BODY()

	TWeakObjectPtr<ACharacter> _targetCharacter;

	FVector _cameraVector;
	FRotator _cameraRotator;

	void CameraXInputBinding(float value);
	void CameraYInputBinding(float value);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float _cameraSpeed = 50.f;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TWeakObjectPtr<UCameraComponent> _cameraComponent;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TWeakObjectPtr<USpringArmComponent> _springArmComponent;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	const FRotator& GetCameraRotator() const;

	UFUNCTION(BlueprintCallable)
	void SetupPlayerInputComponent(APlayerController* playerController);
	UFUNCTION(BlueprintCallable)
	void SetTargetCharacter(ACharacter* character);
};
