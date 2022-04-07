#include "NPC/Movement/PINpcPathController.h"

FPINpcPathController::FPINpcPathController(const TArray<FVector>& pathNodes, const bool loop)
{
	_pathNodes = pathNodes;
	_currentNode = 0;
	_loop = loop;
}

void FPINpcPathController::BeginPath()
{
	_currentNode = 0;
}


