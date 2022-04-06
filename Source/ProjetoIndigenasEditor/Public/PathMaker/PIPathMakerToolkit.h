#pragma once
#include "PIPathMakerWidget.h"

class FPIPathMakerToolkit : public FModeToolkit
{
	TSharedPtr<SPIPathMakerWidget> _modeWidget;
	
public:
	FPIPathMakerToolkit();

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<SWidget> GetInlineContent() const override;

	void SetInfoText(const FString& infoText) const;
	void SetObjectPath(const FString& objectPath) const;
};
