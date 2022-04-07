#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FPIDestinationController
{
private:
	TArray<FVector> _nodes;

	int _currentIndex = 0;
	bool _cycleDestination = false;

	void NextIndex();

public:
	FPIDestinationController(TArray<FVector> nodes, bool cycleDestination = true);
	~FPIDestinationController() = default;
	
	bool HasDestination() const;
	bool NextDestination(FVector& outVector);
	FVector GetCurrentDestination() const;
	bool IsPathCompleted() const;
};
