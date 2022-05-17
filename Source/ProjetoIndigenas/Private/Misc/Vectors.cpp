#include "Misc/Vectors.h"

#pragma region FAcceleratedValue

FAcceleratedValue FAcceleratedValue::ZeroValue = FAcceleratedValue();

void FAcceleratedValue::Tick(float DeltaSeconds)
{
	const float delta = Target - Current;

	float step = FMath::Abs(delta) * Acceleration * DeltaSeconds;
	
	if (Target < Current) step = -step;

	if (FMath::Abs(step) > FMath::Abs(delta))
	{
		Current = Target;
		
		return;
	}
	
	Current += step;
}

#pragma endregion FAcceleratedValue

#pragma region FAcceleratedVector2D

FAcceleratedVector2D FAcceleratedVector2D::ZeroVector2D = FAcceleratedVector2D();

FAcceleratedVector2D::FAcceleratedVector2D()
{
	X = FAcceleratedValue::ZeroValue;
	Y = FAcceleratedValue::ZeroValue;
}

void FAcceleratedVector2D::Tick(float DeltaSeconds)
{
	X.Tick(DeltaSeconds);
	Y.Tick(DeltaSeconds);
}

void FAcceleratedVector2D::SetAcceleration(float acceleration)
{
	X.Acceleration = acceleration;
	Y.Acceleration = acceleration;
}

#pragma endregion FAcceleratedVector2D

#pragma region FAcceleratedVector

FAcceleratedVector FAcceleratedVector::ZeroVector = FAcceleratedVector();

FAcceleratedVector::FAcceleratedVector()
{
	X = FAcceleratedValue::ZeroValue;
	Y = FAcceleratedValue::ZeroValue;
	Z = FAcceleratedValue::ZeroValue;
}

void FAcceleratedVector::Tick(float DeltaSeconds)
{
	FAcceleratedVector2D::Tick(DeltaSeconds);
	
	Z.Tick(DeltaSeconds);
}

void FAcceleratedVector::SetAcceleration(float acceleration)
{
	FAcceleratedVector2D::SetAcceleration(acceleration);

	Z.Acceleration = acceleration;
}

#pragma endregion FAcceleratedVector
