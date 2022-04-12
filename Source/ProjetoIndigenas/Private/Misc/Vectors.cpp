#include "Misc/Vectors.h"

#pragma region FAcceleratedValue

FAcceleratedValue FAcceleratedValue::ZeroValue = FAcceleratedValue();

void FAcceleratedValue::Tick(float DeltaSeconds)
{
	const float delta = _target - _current;

	float step = FMath::Abs(delta) * Acceleration * DeltaSeconds;
	
	if (_target < _current) step = -step;

	if (FMath::Abs(step) > FMath::Abs(delta))
	{
		_current = _target;
		
		return;
	}
	
	_current += step;
}

#pragma endregion FAcceleratedValue

#pragma region FAcceleratedVector2D

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
