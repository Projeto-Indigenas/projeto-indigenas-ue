#include "ClimbableTree/PIClimbableTreeCustomEditor.h"

#include <CanvasTypes.h>
#include <EditorViewportClient.h>

#include "LevelEditorViewport.h"
#include "Debug/PIPathDrawer.h"

bool FPIClimbableTreeCustomEditor::IsEditorForClass(UClass* cls)
{
	return cls->IsChildOf(APIClimbableTree::StaticClass());
}

void FPIClimbableTreeCustomEditor::EndEditing()
{
	_climbableTree = nullptr;
	_staticMeshComponent = nullptr;
	_socketsLocations.Empty();
}

void FPIClimbableTreeCustomEditor::DrawVisualization(
	const UActorComponent* Component,
	FEditorViewportClient* ViewportClient,
	FPrimitiveDrawInterface* PDI)
{
	if (!_climbableTree.IsValid() || _climbableTree != Component->GetOwner())
	{
		_climbableTree = Cast<APIClimbableTree>(Component->GetOwner());

		if (!_climbableTree.IsValid()) return;

		UActorComponent* component = _climbableTree->GetComponentByClass(UStaticMeshComponent::StaticClass());
		_staticMeshComponent = Cast<UStaticMeshComponent>(component);

		if (!_staticMeshComponent.IsValid()) return;

		_socketsLocations.Empty();
		for (const FName& socketName : _staticMeshComponent->GetAllSocketNames())
		{
			const FVector& location = _staticMeshComponent->GetSocketLocation(socketName);
			_socketsLocations.Add(location);
		}
	}

	if (!_climbableTree.IsValid()) return;
	
	DrawPath(PDI, _socketsLocations);

	if (_socketsLocations.Num() > 0)
	{
		const FVector& baseLocation = _socketsLocations[0];

		for (const TTuple<EPIClimbingState, float>& pair : _climbableTree->GetPositionRadiusMap())
		{
			DrawCircle(PDI, baseLocation, FVector::ForwardVector, FVector::RightVector,
				FLinearColor::MakeFromColorTemperature(pair.Value), pair.Value, 10, 0, 1.f);
		}
	}
}
