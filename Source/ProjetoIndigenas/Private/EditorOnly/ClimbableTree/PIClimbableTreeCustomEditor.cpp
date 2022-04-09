#include "EditorOnly/ClimbableTree/PIClimbableTreeCustomEditor.h"

#if WITH_EDITOR

#include "EditorOnly/Debug/PIPathDrawer.h"

FPIClimbableTreeCustomEditor::FPIClimbableTreeCustomEditor(APIClimbableTree* climbableTree)
{
	_climbableTree = climbableTree;
}

void FPIClimbableTreeCustomEditor::DrawVisualization(FPrimitiveDrawInterface* PDI)
{
	DrawPath(PDI, _climbableTree->_climbableTrack);

	if (_climbableTree->_climbableTrack.Num() > 0)
	{
		const FVector& baseLocation = _climbableTree->GetActorLocation() + _climbableTree->_climbableTrack[0];
		DrawCircle(PDI, baseLocation, FVector::ForwardVector, FVector::RightVector,
			FLinearColor::Red, _climbableTree->_startPositionRadius, 10, 0, 1.f);
	}
}

void FPIClimbableTreeCustomEditor::DrawVisualizationHUD(FCanvas* Canvas)
{
	const TCHAR* infoText = TEXT(
		"Climbable Tree Path Editor\n"
		"Use the following commands to edit the path:\n"
		"N -> Insert new next to the mouse position;\n"
		"M -> Mark point position;\n"
		"G -> Grab point nearest to mouse;\n"
		"D -> Delete point nearest to mouse;\n"
		"F -> Focus on point;\n"
		"S -> Mark Dirty (Save);"
	);
	
	Canvas->DrawShadowedString(20, 40, infoText, GEngine->GetMediumFont(), FLinearColor::White);
}

#endif
