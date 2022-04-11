﻿#include "ClimbableTree/PIClimbableTreeCustomEditor.h"

#include <CanvasTypes.h>
#include <EditorViewportClient.h>

#include "Debug/PIPathDrawer.h"

bool FPIClimbableTreeCustomEditor::TryGetTargetLocation(
	const UWorld* world,
	const FViewportCursorLocation& mouseLocation,
	FVector& outLocation)
{
	const FVector& mouseOrigin = mouseLocation.GetOrigin();
	const FVector& rayEnd = mouseOrigin + mouseLocation.GetDirection() * 10000.f;
	
	DrawDebugLine(world, mouseOrigin, rayEnd, FColor::Green);

	FHitResult hit;
	if (!world->LineTraceSingleByChannel(hit, mouseOrigin, rayEnd, ECC_WorldStatic)) return false;

	outLocation = hit.Location;
	return hit.GetActor()->IsA<APIClimbableTree>();
}

void FPIClimbableTreeCustomEditor::SetActor(AActor* actor)
{
	_climbableTree = Cast<APIClimbableTree>(actor);
}

bool FPIClimbableTreeCustomEditor::IsEditorForClass(UClass* cls)
{
	return cls->IsChildOf(APIClimbableTree::StaticClass());
}

TArray<FVector>& FPIClimbableTreeCustomEditor::GetNodes() const
{
	return _climbableTree->GetTrack();
}

void FPIClimbableTreeCustomEditor::DrawVisualization(FPrimitiveDrawInterface* PDI)
{
	if (!_climbableTree.IsValid()) return;
	
	const TArray<FVector>& track = _climbableTree->GetTrack();
	
	DrawPath(PDI, track);

	if (track.Num() > 0)
	{
		const FVector& baseLocation = _climbableTree->GetActorLocation() + track[0];
		DrawCircle(PDI, baseLocation, FVector::ForwardVector, FVector::RightVector,
			FLinearColor::Red, _climbableTree->GetStartPositionRadius(), 10, 0, 1.f);
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

bool FPIClimbableTreeCustomEditor::HandleInputKey(
	FEditorViewportClient* ViewportClient,
	const FKey& Key,
	const EInputEvent& Event)
{
	if (!_climbableTree.IsValid()) return false;

	if (Event == IE_Pressed && !Key.IsMouseButton())
	{
		const FViewportCursorLocation& location = ViewportClient->GetCursorWorldLocationFromMousePos();
		
		FVector mouseLocation;
		if (!TryGetTargetLocation(_climbableTree->GetWorld(), location, mouseLocation)) return false;
				
		if (Key == EKeys::N) // new
			{
			CreateNewVector(mouseLocation);
			return true;
			}

		if (Key == EKeys::M) // mark
			{
			FinishPlacingNode();
			return true;
			}

		if (Key == EKeys::G) // grab nearest
			{
			GrabNearestVector(mouseLocation);
			return true;
			}

		if (Key == EKeys::D) // delete nearest
			{
			DeleteNearestVector(mouseLocation);
			return true;
			}

		if (Key == EKeys::F)
		{
			FocusNearestVector(ViewportClient, mouseLocation);
			return true;
		}

		if(Key == EKeys::S)
		{
			Save();
			return true;
		}
	}
	
	return false;
}
