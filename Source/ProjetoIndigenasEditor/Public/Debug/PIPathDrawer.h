#pragma once

#include "CoreMinimal.h"

extern PROJETOINDIGENASEDITOR_API
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
	const float& lineThickness = 1.f,
	const FVector& worldZero = FVector::ZeroVector);

inline void DrawPath(
	FPrimitiveDrawInterface* PDI,
	const TArray<FVector>& path,
	const FVector& worldZero)
{
	DrawPath(
		PDI,
		path,
		FLinearColor::Green,
		FLinearColor::Blue,
		FLinearColor::Red,
		10.f,
		5.0f,
		20.f,
		FLinearColor::Red,
		1.f,
		worldZero);
}
