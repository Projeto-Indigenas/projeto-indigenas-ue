#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FDestinationController
{
private:
	TArray<FVector> _nodes;

	int _currentIndex = 0;
	bool _cycleDestination = false;

	void NextIndex();

public:
	FDestinationController(TArray<FVector> nodes, bool cycleDestination = true);
	~FDestinationController() = default;
	
	bool HasDestination() const;
	bool NextDestination(FVector& outVector);
	FVector GetCurrentDestination() const;
	bool IsPathCompleted() const;
};
