#include "Beings/NPC/Paths/PIDestinationController.h"

void FPIDestinationController::NextIndex()
{
	++_currentIndex;

	if (!_cycleDestination) return;

	_currentIndex %= _nodes.Num();
}

FPIDestinationController::FPIDestinationController(TArray<FVector> nodes, bool cycleDestination)
{
	_nodes = nodes;
	_cycleDestination = cycleDestination;
}

bool FPIDestinationController::HasDestination() const
{
	return _nodes.Num() > 0;
}

bool FPIDestinationController::NextDestination(FVector& outVector)
{
	if (IsPathCompleted()) return false;

	outVector = _nodes[_currentIndex];
	NextIndex();
	return true;
}

FVector FPIDestinationController::GetCurrentDestination() const
{
	if (IsPathCompleted()) return _nodes.Last();

	return _nodes[_currentIndex];
}

bool FPIDestinationController::IsPathCompleted() const
{
	return !_cycleDestination && _currentIndex >= _nodes.Num();
}
