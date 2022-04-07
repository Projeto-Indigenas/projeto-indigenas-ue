#include "UI/PIHUDBase.h"

#include "Misc/Logging.h"

void APIHUDBase::BeginPlay()
{
	Super::BeginPlay();

	_gameFlowSubsystem = GetGameInstance()->GetSubsystem<UPIGameFlowSubsystem>();
}

void APIHUDBase::TransitionTo(const FName state)
{
	if (!_gameFlowSubsystem.IsValid())
	{
		PI_LOGV_UOBJECT(Error, TEXT("Somehow the Game flow subsystem is invalid"))

		return;
	}
	
	_gameFlowSubsystem->TransitionTo(state);
}


