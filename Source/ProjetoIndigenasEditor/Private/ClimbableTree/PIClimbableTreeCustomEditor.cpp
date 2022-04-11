#include "ClimbableTree/PIClimbableTreeCustomEditor.h"

#include <CanvasTypes.h>
#include <EditorViewportClient.h>

#include "FileHelpers.h"
#include "LevelEditorViewport.h"
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
	if (!world->LineTraceSingleByChannel(hit, mouseOrigin, rayEnd, ECC_Camera)) return false;

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

void FPIClimbableTreeCustomEditor::DrawVisualization(
	FEditorViewportClient* ViewportClient,
	FPrimitiveDrawInterface* PDI)
{
	if (!_climbableTree.IsValid()) return;
	
	const TArray<FVector>& track = _climbableTree->GetTrack();
	
	DrawPath(PDI, track, _climbableTree->GetActorLocation());

	if (track.Num() > 0)
	{
		const FVector& baseLocation = GetWorldVector(track[0]);
		DrawCircle(PDI, baseLocation, FVector::ForwardVector, FVector::RightVector,
			FLinearColor::Red, _climbableTree->GetStartPositionRadius(), 10, 0, 1.f);
	}

	if (GetCurrentNode() == nullptr) return;

	const FViewportCursorLocation& location = ViewportClient->GetCursorWorldLocationFromMousePos();
		
	FVector mouseLocation;
	if (TryGetTargetLocation(_climbableTree->GetWorld(), location, mouseLocation))
	{
		mouseLocation -= _climbableTree->GetActorLocation();
		SetCurrentNodeValue(mouseLocation);
	}
	
	MakeInfoText(TEXT("Placing node"));
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
		if(Key == EKeys::S)
		{
			Save();
			return true;
		}
		
		const FViewportCursorLocation& location = ViewportClient->GetCursorWorldLocationFromMousePos();
		
		
		FVector mouseLocation;
		if (!TryGetTargetLocation(_climbableTree->GetWorld(), location, mouseLocation)) return false;

		mouseLocation -= _climbableTree->GetActorLocation();
				
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
	}
	
	return false;
}

void FPIClimbableTreeCustomEditor::MarkDirty()
{
	if (!_climbableTree.IsValid()) return;
	_climbableTree->MarkPackageDirty();
}

void FPIClimbableTreeCustomEditor::Save()
{
	FPIPathEditorBase::Save();
	
	TArray<UPackage*> toSave;
	toSave.Add(_climbableTree->GetPackage());
	UEditorLoadingAndSavingUtils::SavePackages(toSave, true);
}

FVector FPIClimbableTreeCustomEditor::GetWorldVector(FVector vector)
{
	return vector + _climbableTree->GetActorLocation();
}
