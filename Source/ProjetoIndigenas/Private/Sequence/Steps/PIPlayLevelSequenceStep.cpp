#include "Sequence/Steps/PIPlayLevelSequenceStep.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Actions/PISkipCutsceneAction.h"
#include "Beings/Player/PIPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Misc/Logging.h"

void UPIPlayLevelSequenceStep::PlaybackFinished()
{
	if (!_sequenceActor.IsValid())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Playback finished but Sequence Actor is invalid, destroy ahead of its time?"))
	}
	else
	{
		ULevelSequencePlayer* player = _sequenceActor->GetSequencePlayer();
		player->OnFinished.RemoveDynamic(this, &UPIPlayLevelSequenceStep::PlaybackFinished);
	}

	Finish(skipped);
}

void UPIPlayLevelSequenceStep::ExecuteStep()
{
	if (!_sequenceActor.IsValid())
	{
		PI_LOGVF_UOBJECT(Error, TEXT("Sequence Actor is invalid"))

		Finish();

		return;
	}

	_sequenceActor->SetSequence(_levelSequenceToPlay);
	
	ULevelSequencePlayer* player = _sequenceActor->GetSequencePlayer();

	if (_setViewTarget)
	{
		const UCameraComponent* cameraComponent = player->GetActiveCameraComponent();

		if (cameraComponent != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->SetViewTarget(cameraComponent->GetOwner());
		}
	}

	
	player->OnFinished.AddUniqueDynamic(this, &UPIPlayLevelSequenceStep::PlaybackFinished);
	player->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(0.f, EUpdatePositionMethod::Jump));
	player->Play();

	APIPlayerController* playerController = Cast<APIPlayerController>(
		_gameInstance->GetFirstLocalPlayerController());

	if (playerController == nullptr) return;
	
	_skipCutsceneAction = MakeShared<FPISkipCutsceneAction>(this);
	playerController->SetAvailableAction(_skipCutsceneAction);
}

void UPIPlayLevelSequenceStep::Skip()
{
	skipped = true;
	
	ULevelSequencePlayer* player = _sequenceActor->GetSequencePlayer();
	const FMovieSceneSequencePlaybackParams& params = FMovieSceneSequencePlaybackParams(
		FMath::Max(player->GetFrameDuration(), 0), EUpdatePositionMethod::Jump);
	player->SetPlaybackPosition(params);
}
