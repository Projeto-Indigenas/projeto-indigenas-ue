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
	const float delta = Target - _current;

	float step = FMath::Abs(delta) * Acceleration * DeltaSeconds;
	if (Target < _current) step = -step;

	if (FMath::Abs(step) > FMath::Abs(delta))
	{
		_current = Target;
		return;
	}
	
	_current += step;
}

float FAcceleratedValue::GetCurrent() const
{
	return _current;
}

FAcceleratedValue::operator float() const
{
	return _current;
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

void FAcceleratedVector2D::SetTarget(FVector2D value)
{
	X.Target = value.X;
	Y.Target = value.Y;
}

FVector2D FAcceleratedVector2D::GetVector2D() const
{
	return FVector2D(X, Y);
}

FRotator FAcceleratedVector2D::GetRotator() const
{
	return FVector(X, Y, 0.f).Rotation();
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

void FAcceleratedVector::SetTarget(FVector value)
{
	FAcceleratedVector2D::SetTarget(FVector2D(value.X, value.Y));

	Z.Target = value.Z;
}

FVector FAcceleratedVector::GetVector() const
{
	return FVector(X, Y, Z);
}

FRotator FAcceleratedVector::GetRotator() const
{
	return GetVector().Rotation();
}

#pragma endregion FAcceleratedVector
