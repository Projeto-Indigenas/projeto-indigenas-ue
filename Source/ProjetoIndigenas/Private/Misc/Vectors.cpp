#include "Misc/Vectors.h"

#pragma region FAcceleratedValue

FAcceleratedValue FAcceleratedValue::ZeroValue = FAcceleratedValue();

FAcceleratedValue::FAcceleratedValue(float current, float acceleration) : FAcceleratedValue()
{
	_current = current;
	Acceleration = acceleration;
}

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

FAcceleratedVector2D::FAcceleratedVector2D(FVector2D current, float acceleration)
{
	X = FAcceleratedValue(current.X, acceleration);
	Y = FAcceleratedValue(current.Y, acceleration);
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

FAcceleratedVector::FAcceleratedVector(FVector current, float acceleration) :
	FAcceleratedVector2D(FVector2D(current.X, current.Y), acceleration)
{
	Z = FAcceleratedValue(current.Z, acceleration);
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
