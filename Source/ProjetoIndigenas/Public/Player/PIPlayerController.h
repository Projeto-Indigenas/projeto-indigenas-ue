#pragma once

#include "CoreMinimal.h"
#include "PICharacter.h"
#include "Input/PIInputDelegates.h"
#include "PIPlayerController.generated.h"

class APICameraController;

UCLASS()
class PROJETOINDIGENAS_API APIPlayerController : public APlayerController
{
	GENERATED_BODY()

	TSharedPtr<FPIInputDelegates> _inputDelegates;
	TWeakObjectPtr<APICharacter> _character;

	void MoveXInputBinding(float x);
	void MoveYInputBinding(float y);
	void ToggleRunInputBinding();
	void DodgeInputBinding();
	void PositiveActionInputBinding();
	void NegativeActionInputBinding();

protected:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TWeakObjectPtr<APICameraController> _cameraController;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;
};
