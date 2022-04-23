#pragma once

#include "CoreMinimal.h"
#include "PICharacter.h"
#include "PIPlayerController.generated.h"

class APICameraController;

UCLASS()
class PROJETOINDIGENAS_API APIPlayerController : public APlayerController
{
	GENERATED_BODY()

	TWeakObjectPtr<APICharacter> _character;

	void MoveXInputBinding(float x);
	void MoveYInputBinding(float y);
	void ToggleRunInputBinding();
	void DodgeInputBinding();
	void PositiveActionInputBinding();
	void NegativeActionInputBinding();

protected:
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<APICameraController> _cameraController;

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetCameraControllerConfigureAndSetAsViewTarget(APICameraController* cameraController);
};
