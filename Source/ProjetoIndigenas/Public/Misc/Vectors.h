#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FAcceleratedValue
{
private:
	float _current = 0.f;
	float _target = 0.f;
	
public:
	static FAcceleratedValue ZeroValue;
	
	float Acceleration = 1.f;
	
	FAcceleratedValue() = default;

	void Tick(float DeltaSeconds);

	FORCEINLINE operator float() const { return _current; }
	FORCEINLINE void operator =(float value) { _target = value; }

	FORCEINLINE void SetCurrent(float value)
	{
		_current = value;
		_target = value;
	}

	FORCEINLINE bool IsOnTarget(const float& tolerance = 0.01f) const
	{
		return FMath::Abs(_current - _target) < tolerance;
	}
};

struct PROJETOINDIGENAS_API FAcceleratedVector2D
{
	FAcceleratedValue X;
	FAcceleratedValue Y;

	FAcceleratedVector2D();
	virtual ~FAcceleratedVector2D() = default;
	
	virtual void Tick(float DeltaSeconds);
	virtual void SetAcceleration(float acceleration);

	FORCEINLINE virtual bool IsOnTarget(const float& tolerance = 0.01f) const
	{
		return X.IsOnTarget(tolerance) && Y.IsOnTarget(tolerance);
	}

	FORCEINLINE operator FVector2D() const { return FVector2D(X, Y); }
	FORCEINLINE virtual operator FVector() const { return FVector(X, Y, 0.f); }
	FORCEINLINE virtual operator FRotator() const { return FVector(X, Y, 0.f).Rotation(); }
	FORCEINLINE void operator =(const FVector2D& value) { X = value.X; Y = value.Y; }
	FORCEINLINE virtual void operator =(const FVector& value) { X = value.X; Y = value.Y; }

	FORCEINLINE void SetCurrent(FVector2D value)
	{
		X.SetCurrent(value.X);
		Y.SetCurrent(value.Y);
	}

	FORCEINLINE virtual void SetCurrent(FVector value)
	{
		X.SetCurrent(value.X);
		Y.SetCurrent(value.Y);
	}
};

struct PROJETOINDIGENAS_API FAcceleratedVector : FAcceleratedVector2D
{
	FAcceleratedValue Z;

	FAcceleratedVector();

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetAcceleration(float acceleration) override;

	FORCEINLINE virtual bool IsOnTarget(const float& tolerance = 0.01f) const override
	{
		return FAcceleratedVector2D::IsOnTarget(tolerance) && Z.IsOnTarget(tolerance);
	}
	
	FORCEINLINE virtual operator FVector() const override { return FVector(X, Y, Z); }
	FORCEINLINE virtual operator FRotator() const override { return FVector(X, Y, Z).Rotation(); }
	FORCEINLINE virtual void operator =(const FVector& value) override
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}
	
	FORCEINLINE virtual void SetCurrent(FVector value) override
	{
		FAcceleratedVector2D::SetCurrent(value);
		Z.SetCurrent(value.Z);
	}
};
