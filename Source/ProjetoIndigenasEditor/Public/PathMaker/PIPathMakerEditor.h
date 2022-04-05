#pragma once

#include "UnrealEd.h"
#include "NPC/Paths/PIPathData.h"

class FPIPathMakerEditor : public FEdMode
{
private:
	UPROPERTY()
	UPIPathData* _editingPath;
	
public:
	const static FEditorModeID EditorModeID;

	virtual void Enter() override;
	virtual void Exit() override;

	void SetEditingPath(UPIPathData* pathData);
};
