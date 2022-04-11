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
	FAcceleratedValue(float current, float acceleration);

	void Tick(float DeltaSeconds);
	
	FORCEINLINE operator float() const { return _current; }
	FORCEINLINE void operator =(float value) { _target = value; }
};

struct PROJETOINDIGENAS_API FAcceleratedVector2D
{
	FAcceleratedValue X;
	FAcceleratedValue Y;

	FAcceleratedVector2D();
	FAcceleratedVector2D(FVector2D current, float acceleration);
	virtual ~FAcceleratedVector2D() = default;
	
	virtual void Tick(float DeltaSeconds);
	virtual void SetAcceleration(float acceleration);

	FORCEINLINE operator FVector2D() const { return FVector2D(X, Y); }
	FORCEINLINE virtual operator FVector() const { return FVector(X, Y, 0.f); }
	FORCEINLINE virtual operator FRotator() const { return FVector(X, Y, 0.f).Rotation(); }
	FORCEINLINE void operator =(const FVector2D& value) { X = value.X; Y = value.Y; }
};

struct PROJETOINDIGENAS_API FAcceleratedVector : FAcceleratedVector2D
{
	FAcceleratedValue Z;

	FAcceleratedVector();
	FAcceleratedVector(FVector current, float acceleration);

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetAcceleration(float acceleration) override;
	
	FORCEINLINE virtual operator FVector() const override { return FVector(X, Y, Z); }
	FORCEINLINE virtual operator FRotator() const override { return FVector(X, Y, Z).Rotation(); }
	FORCEINLINE void operator =(const FVector& value) { X = value.X; Y = value.Y; Z = value.Z; }
};
