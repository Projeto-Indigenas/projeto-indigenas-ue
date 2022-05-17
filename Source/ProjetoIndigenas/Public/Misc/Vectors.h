#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FAcceleratedValue
{
	static FAcceleratedValue ZeroValue;

	float Current = 0.f;
	float Target = 0.f;
	float Acceleration = 1.f;
	
	FAcceleratedValue() = default;

	void Tick(float DeltaSeconds);

	FORCEINLINE operator float() const { return Current; }
	FORCEINLINE void operator =(float value) { Target = value; }

	FORCEINLINE bool IsOnTarget(const float& tolerance = 0.01f) const
	{
		return FMath::Abs(Current - Target) <= tolerance;
	}
};

struct PROJETOINDIGENAS_API FAcceleratedVector2D
{
	static FAcceleratedVector2D ZeroVector2D;
	
	FAcceleratedValue X;
	FAcceleratedValue Y;

	FAcceleratedVector2D();
	virtual ~FAcceleratedVector2D() = default;
	
	virtual void Tick(float DeltaSeconds);
	virtual void SetAcceleration(float acceleration);

	FORCEINLINE virtual FVector2D GetTarget2D() const { return FVector2D(X.Target, Y.Target); }
	FORCEINLINE virtual FVector GetTarget() const { return FVector(X.Target, Y.Target, 0.f); }

	FORCEINLINE void SetCurrent(FVector2D value)
	{
		X.Current = value.X;
		Y.Current = value.Y;
	}

	FORCEINLINE virtual void SetCurrent(FVector value)
	{
		X.Current = value.X;
		Y.Current = value.Y;
	}

	FORCEINLINE virtual void SetCurrent(FRotator rotator)
	{
		const FVector& vector = rotator.Vector();
		X.Current = vector.X;
		Y.Current = vector.Y;
	}	
	
	FORCEINLINE operator FVector2D() const { return FVector2D(X, Y); }
	FORCEINLINE virtual operator FVector() const { return FVector(X, Y, 0.f); }
	FORCEINLINE virtual operator FRotator() const { return FVector(X, Y, 0.f).Rotation(); }
	FORCEINLINE void operator =(const FVector2D& value) { X = value.X; Y = value.Y; }
	FORCEINLINE virtual void operator =(const FVector& value) { X = value.X; Y = value.Y; }
	FORCEINLINE virtual void operator =(const FRotator& value)
	{
		const FVector& vector = value.Vector();
		X = vector.X;
		Y = vector.Y;
	}

	FORCEINLINE virtual bool IsOnTarget(const float& tolerance = 0.01f) const
	{
		return X.IsOnTarget(tolerance) && Y.IsOnTarget(tolerance);
	}
};

struct PROJETOINDIGENAS_API FAcceleratedVector : FAcceleratedVector2D
{
	static FAcceleratedVector ZeroVector;
	
	FAcceleratedValue Z;

	FAcceleratedVector();

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetAcceleration(float acceleration) override;

	FORCEINLINE virtual FVector GetTarget() const override { return FVector(X.Target, Y.Target, Z.Target); }
	FORCEINLINE virtual FRotator GetTargetRotator() const { return GetTarget().Rotation(); }
	
	FORCEINLINE virtual void SetCurrent(FVector value) override
	{
		FAcceleratedVector2D::SetCurrent(value);
		Z.Current = value.Z;
	}

	FORCEINLINE virtual void SetCurrent(FRotator rotator) override
	{
		const FVector& vector = rotator.Vector();
		X.Current = vector.X;
		Y.Current = vector.Y;
		Z.Current = vector.Z;
	}
	
	FORCEINLINE virtual operator FVector() const override { return FVector(X, Y, Z); }
	FORCEINLINE virtual operator FRotator() const override { return FVector(X, Y, Z).Rotation(); }
	FORCEINLINE virtual void operator =(const FVector& value) override
	{
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	FORCEINLINE virtual void operator =(const FRotator& value) override
	{
		const FVector& vector = value.Vector();
		X = vector.X;
		Y = vector.Y;
		Z = vector.Z;
	}

	FORCEINLINE virtual bool IsOnTarget(const float& tolerance = 0.01f) const override
	{
		return FAcceleratedVector2D::IsOnTarget(tolerance) && Z.IsOnTarget(tolerance);
	}
};
