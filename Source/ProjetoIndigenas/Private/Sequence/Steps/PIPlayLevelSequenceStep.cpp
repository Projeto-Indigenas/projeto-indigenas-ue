#include "Sequence/Steps/PIPlayLevelSequenceStep.h"

#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
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

	Finish();
}

void UPIPlayLevelSequenceStep::ExecuteStep()
{
	Super::ExecuteStep();

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
}
