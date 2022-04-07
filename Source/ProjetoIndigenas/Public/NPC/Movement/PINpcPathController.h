#pragma once

#include "CoreMinimal.h"

struct PROJETOINDIGENAS_API FPINpcPathController
{
private:
	TArray<FVector> _pathNodes;
	int _currentNode;
	bool _loop;

public:
	FPINpcPathController(const TArray<FVector>& pathNodes, const bool loop);

	void BeginPath();
};
