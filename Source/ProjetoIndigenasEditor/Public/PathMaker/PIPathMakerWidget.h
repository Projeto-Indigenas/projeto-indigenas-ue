#pragma once

class SPIPathMakerWidget : public SCompoundWidget
{
	TSharedPtr<FAssetThumbnailPool> _thumbnailPool;

	FString GetPathObject() const;
	void OnPathObjectChanged(const FAssetData& assetData) const;
	
public:
	SLATE_BEGIN_ARGS(SPIPathMakerWidget) { }
	SLATE_END_ARGS()

	FString ObjectPath;
	FString InfoText;

	void Construct(const FArguments& inArgs);

	static class FPIPathMakerEditor* GetEdMode();
};


