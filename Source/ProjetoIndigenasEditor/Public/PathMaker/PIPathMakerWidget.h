#pragma once

class SPIPathMakerWidget : public SCompoundWidget
{
	FString _objectPath;
	TSharedPtr<FAssetThumbnailPool> _thumbnailPool;

	FString GetPathObject() const;
	void OnPathObjectChanged(const FAssetData& assetData);
	
public:
	SLATE_BEGIN_ARGS(SPIPathMakerWidget) { }
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs);

	static class FPIPathMakerEditor* GetEdMode();
};


