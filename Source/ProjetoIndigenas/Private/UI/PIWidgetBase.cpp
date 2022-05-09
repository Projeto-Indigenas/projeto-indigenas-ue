#include "UI/PIWidgetBase.h"

APIHUDBase* UPIWidgetBase::GetHUD() const
{
	const APlayerController* controller = GetOwningPlayer();
	if (controller == nullptr) return nullptr;
	return Cast<APIHUDBase>(controller->GetHUD());
}
