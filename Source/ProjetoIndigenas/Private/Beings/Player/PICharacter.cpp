#include "Beings/Player/PICharacter.h"

#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Shared/States/PIMovementState.h"
#include "Interactables/PIClimbableTree.h"
#include "Misc/Logging.h"

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateMovementState(
		_capsuleRadiusForState[EPICharacterAnimationState::Movement],
		_movementAccelerationForState[EPICharacterAnimationState::Movement]);
	
	CreateClimbingState(
		_capsuleRadiusForState[EPICharacterAnimationState::Climbing],
		_movementAccelerationForState[EPICharacterAnimationState::Climbing]);
}

void APICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	SetCurrentState(_movementState);
}

void APICharacter::UnPossessed()
{
	Super::UnPossessed();

	SetCurrentState(nullptr);
}

void APICharacter::StartClimbing(APIClimbableTree* tree)
{
	_climbingState->Tree = tree;
	SetCurrentState(_climbingState);
}

void APICharacter::StopClimbing(APIClimbableTree* tree)
{
	SetCurrentState(_movementState);
}

void APICharacter::SetupCharacterBody(USkeletalMeshComponent* bodyComponent, USkeletalMeshComponent* faceComponent)
{
	const UPISaveGameSubsystem* saveGameSubsystem = GetGameInstance()->GetSubsystem<UPISaveGameSubsystem>();

	if (saveGameSubsystem == nullptr)
	{
		PI_LOGV_UOBJECT(Warning, TEXT("SaveGameSubsystem should never be nullptr, using default skin"))

		return;
	}

	const UPICharacterConfigurationSettings* settings = GetDefault<UPICharacterConfigurationSettings>();

	if (settings == nullptr)
	{
		PI_LOGV_UOBJECT(Warning, TEXT("CharacterConfigurationSettings should never be nullptr, using default skin"))

		return;
	}

	const UPICharacterConfigurationData* configurationData = settings->CharacterConfigurationData.LoadSynchronous();

	if (configurationData == nullptr)
	{
		PI_LOGV_UOBJECT(Warning, TEXT("CharacterConfigurationData shouldn't be nullptr, using default skin"))

		return;
	}
	
	const FPIPlayerCharacterSavedData& characterData = saveGameSubsystem->PlayerCharacterData;

	if (characterData.CharacterId.IsNone())
	{
		PI_LOGV_UOBJECT(Warning, TEXT("No character Id in save data, using default skin"))

		return;
	}

	const FPICharacterConfiguration* configPtr = configurationData->PlayerCharactersMap.Find(characterData.CharacterId);

	if (configPtr == nullptr)
	{
		PI_LOGVF_UOBJECT(Warning, TEXT("No configuration available for CharacterId (%s), using default skin"),
			*characterData.CharacterId.ToString())

		return;
	}

	// TODO(anderson): in the future we need to know which version of the body to load
	const TObjectPtr<UPIMetaHumanBodyConfigData>& config = configPtr->ChildBodyConfig;

	bodyComponent->SetSkeletalMesh(config->CharacterBody.LoadSynchronous());
	faceComponent->SetSkeletalMesh(config->CharacterFace.LoadSynchronous());
}
