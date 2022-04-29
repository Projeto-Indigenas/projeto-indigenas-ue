#pragma once

#include "CoreMinimal.h"
#include "PICharacterAnimInstance.h"
#include "Beings/Shared/PICharacterBase.h"
#include "Beings/Shared/Config/PICharacterConfigurationSettings.h"
#include "SavedData/PISaveGameSubsystem.h"
#include "PICharacter.generated.h"

UCLASS()
class PROJETOINDIGENAS_API APICharacter : public APICharacterBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _capsuleRadiusForState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EPICharacterAnimationState, float> _movementAccelerationForState;
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	
public:
	virtual void StartClimbing(APIClimbableTree* tree) override;
	virtual void StopClimbing(APIClimbableTree* tree) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetupCharacterBody(
		USkeletalMeshComponent* bodyComponent,
		USkeletalMeshComponent* faceComponent);
};
