#pragma once

#include "CoreMinimal.h"

extern PROJETOINDIGENAS_API
void DrawPath(
	FPrimitiveDrawInterface* PDI,
	const TArray<FVector>& path,
	const FLinearColor& startNodeColor = FLinearColor::Green,
	const FLinearColor& middleNodeColor = FLinearColor::Blue,
	const FLinearColor& endNodeColor = FLinearColor::Red,
	const float& startNodeSize = 10.f,
	const float& middleNodeSize = 5.f,
	const float& endNodeSize = 20.f,
	const FLinearColor& lineColor =  FLinearColor::Red,
	const float& lineThickness = 1.f);
