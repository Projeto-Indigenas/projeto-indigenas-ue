#include "DestinationController.h"

void FDestinationController::NextIndex()
{
	++_currentIndex;

	if (!_cycleDestination) return;

	_currentIndex %= _nodes.Num();
}

FDestinationController::FDestinationController(TArray<FVector> nodes, bool cycleDestination)
{
	_nodes = nodes;
	_cycleDestination = cycleDestination;
}

bool FDestinationController::HasDestination() const
{
	return _nodes.Num() > 0;
}

bool FDestinationController::NextDestination(FVector& outVector)
{
	if (IsPathCompleted()) return false;

	outVector = _nodes[_currentIndex];
	NextIndex();
	return true;
}

FVector FDestinationController::GetCurrentDestination() const
{
	if (IsPathCompleted()) return _nodes.Last();

	return _nodes[_currentIndex];
}

bool FDestinationController::IsPathCompleted() const
{
	return !_cycleDestination && _currentIndex >= _nodes.Num();
}
