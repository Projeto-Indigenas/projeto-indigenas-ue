#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FAcceleratedValue
{
private:
	float _current = 0.f;
	
public:
	static FAcceleratedValue ZeroValue;

	float Target = 0.f;
	float Acceleration = 1.f;
	
	FAcceleratedValue() = default;
	FAcceleratedValue(float current, float acceleration);

	void Tick(float DeltaSeconds);
	
	FORCEINLINE float GetCurrent() const;
	FORCEINLINE operator float() const;
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

	void SetTarget(FVector2D value);
	FORCEINLINE FVector2D GetVector2D() const;
	FORCEINLINE virtual FRotator GetRotator() const;
};

struct PROJETOINDIGENAS_API FAcceleratedVector : FAcceleratedVector2D
{
	FAcceleratedValue Z;

	FAcceleratedVector();
	FAcceleratedVector(FVector current, float acceleration);

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetAcceleration(float acceleration) override;

	void SetTarget(FVector value);
	FORCEINLINE FVector GetVector() const;
	FORCEINLINE virtual FRotator GetRotator() const override;
};
