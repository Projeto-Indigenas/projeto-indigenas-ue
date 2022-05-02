#include "Beings/Player/PICharacter.h"

#include "WaterBodyActor.h"
#include "Beings/Player/PICharacterAnimInstance.h"
#include "Beings/Player/States/PIClimbingState.h"
#include "Beings/Shared/Config/PICharacterConfigurationSettings.h"
#include "Beings/Shared/States/PIMovementState.h"
#include "Interactables/PIClimbableTree.h"
#include "Misc/Logging.h"
#include "SavedData/PISaveGameSubsystem.h"

void APICharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateMovementState(
		_capsuleRadiusForState.FindOrAdd(EPICharacterAnimationState::Movement),
		_movementAccelerationForState.FindOrAdd(EPICharacterAnimationState::Movement));
	
	CreateClimbingState(
		_capsuleRadiusForState.FindOrAdd(EPICharacterAnimationState::Climbing),
		_movementAccelerationForState.FindOrAdd(EPICharacterAnimationState::Climbing));

	CreateSwimmingState(
		_capsuleRadiusForState.FindOrAdd(EPICharacterAnimationState::Swimming),
		_movementAccelerationForState.FindOrAdd(EPICharacterAnimationState::Swimming));

	SetCurrentState(_movementState);
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

void APICharacter::SetupGroomComponent(const FPIMetaHumanGroomConfig& config, UGroomComponent* component)
{
	if (component == nullptr)
	{
		PI_LOGV_UOBJECT(Warning, TEXT("Trying to setup groom with nullptr component"))

		return;
	}
	
	for (int index = 0; index < config.HairMaterials.Num(); ++index)
	{
		component->SetMaterial(index, config.HairMaterials[index].LoadSynchronous());	
	}

	component->SetGroomAsset(
		config.GroomAsset.LoadSynchronous(),
		config.GroomBindingAsset.LoadSynchronous());
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

void APICharacter::StartSwimming(AWaterBody* waterBody)
{
	_swimmingState->WaterBody = waterBody;
	SetCurrentState(_swimmingState);
}

void APICharacter::EndSwimming()
{
	SetCurrentState(_movementState);
}

void APICharacter::SetupCharacterBody(
	USkeletalMeshComponent* bodyComponent,
	USkeletalMeshComponent* faceComponent,
	UGroomComponent* hairComponent,
	UGroomComponent* fuzzComponent,
	UGroomComponent* eyelashesComponent,
	UGroomComponent* eyebrowsComponent)
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

	bodyComponent->SetRelativeScale3D(config->CharacterBodyScale);
	bodyComponent->SetSkeletalMesh(config->CharacterBody.LoadSynchronous());
	faceComponent->SetSkeletalMesh(config->CharacterFace.LoadSynchronous());

	SetupGroomComponent(config->HairConfig, hairComponent);
	SetupGroomComponent(config->FuzzConfig, fuzzComponent);
	SetupGroomComponent(config->EyelashesConfig, eyelashesComponent);
	SetupGroomComponent(config->EyebrowsConfig, eyebrowsComponent);
}
