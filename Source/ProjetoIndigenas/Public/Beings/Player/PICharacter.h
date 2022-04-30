#pragma once

#include "CoreMinimal.h"
#include "GroomComponent.h"
#include "PICharacterAnimInstance.h"
#include "Beings/Shared/PICharacterBase.h"
#include "Beings/Shared/Config/PIMetaHumanBodyConfigData.h"
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

	static void SetupGroomComponent(const FPIMetaHumanGroomConfig& config, UGroomComponent* component);
	
public:
	virtual void StartClimbing(APIClimbableTree* tree) override;
	virtual void StopClimbing(APIClimbableTree* tree) override;
	virtual void StartSwimming(AWaterBody* waterBody) override;
	virtual void EndSwimming(AWaterBody* waterBody) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetupCharacterBody(
		USkeletalMeshComponent* bodyComponent,
		USkeletalMeshComponent* faceComponent,
		UGroomComponent* hairComponent,
		UGroomComponent* fuzzComponent,
		UGroomComponent* eyelashesComponent,
		UGroomComponent* eyebrowsComponent);
};
