#pragma once

#include "CoreMinimal.h"

DECLARE_DELEGATE_OneParam(FPIInputAxisDelegate, float)
DECLARE_DELEGATE_OneParam(FPIInputRotatorDelegate, FRotator)
DECLARE_DELEGATE(FPIInputActionDelegate)

class PROJETOINDIGENAS_API FPIInputDelegates
{
public:
	FPIInputAxisDelegate HorizontalInputDelegate;
	FPIInputAxisDelegate VerticalInputDelegate;
	FPIInputAxisDelegate DirectionPitchDelegate;
	FPIInputAxisDelegate DirectionYawDelegate;
	FPIInputRotatorDelegate CameraRotatorDelegate;
	FPIInputActionDelegate DodgeDelegate;
	FPIInputActionDelegate ToggleRunDelegate;
	FPIInputActionDelegate PositiveActionDelegate;
	FPIInputActionDelegate NegativeActionDelegate;
};
