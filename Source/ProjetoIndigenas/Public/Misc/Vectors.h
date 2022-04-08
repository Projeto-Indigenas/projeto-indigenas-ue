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
	
	FORCEINLINE operator float() const;
	FORCEINLINE void operator =(float value);
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

	FORCEINLINE operator FVector2D() const;
	FORCEINLINE virtual operator FVector() const;
	FORCEINLINE virtual operator FRotator() const;
	FORCEINLINE void operator =(const FVector2D& value);
};

struct PROJETOINDIGENAS_API FAcceleratedVector : FAcceleratedVector2D
{
	FAcceleratedValue Z;

	FAcceleratedVector();
	FAcceleratedVector(FVector current, float acceleration);

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetAcceleration(float acceleration) override;
	
	FORCEINLINE virtual operator FVector() const override;
	FORCEINLINE virtual operator FRotator() const override;
	FORCEINLINE void operator =(const FVector& value);
};
