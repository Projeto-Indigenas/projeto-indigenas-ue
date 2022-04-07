#include "Debug/PIPathDrawer.h"

void DrawPath(
	FPrimitiveDrawInterface* PDI,
	const TArray<FVector>& path,
	const FLinearColor& startNodeColor,
	const FLinearColor& middleNodeColor,
	const FLinearColor& endNodeColor,
	const float& startNodeSize,
	const float& middleNodeSize,
	const float& endNodeSize,
	const FLinearColor& lineColor,
	const float& lineThickness,
	const FVector& worldZero)
{
	constexpr ESceneDepthPriorityGroup depthPriority = SDPG_Foreground;
	
	const int& nodesCount = path.Num();
	
	for (int index = 0; index < nodesCount; ++index)
	{
		const FVector& current = path[index] + worldZero;

		if (index < nodesCount - 1)
		{
			const FVector& next = path[index + 1] + worldZero;

			FLinearColor color;
			float size;
			if (index == 0) 
			{
				color = startNodeColor;
				size = startNodeSize;
			}
			else 
			{
				color = middleNodeColor;
				size = middleNodeSize;
			}
			PDI->DrawPoint(current, color, size, depthPriority);
			
			PDI->DrawLine(current, next, lineColor, depthPriority, lineThickness);

			continue;
		}

		PDI->DrawPoint(current, endNodeColor, endNodeSize, depthPriority);
	}
}
