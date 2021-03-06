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
	float _inputX = 0.f;
	float _inputY = 0.f;

	TSharedPtr<FPIActionBase> _availableAction;

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
	TSharedPtr<FPIInputDelegates> InputDelegates;
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void SetCameraController(APICameraController* cameraController);

	void SetAvailableAction(const TSharedPtr<FPIActionBase>& action);
};
