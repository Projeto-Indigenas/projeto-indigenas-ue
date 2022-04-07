#include "PathMaker/PIPathMakerWidget.h"

#include "EditorModeManager.h"
#include "PropertyCustomizationHelpers.h"
#include "Beings/NPC/Paths/PIPathData.h"
#include "PathMaker/PIPathMakerEditor.h"
#include "Widgets/Layout/SScrollBox.h"

FString SPIPathMakerWidget::GetPathObject() const
{
	return ObjectPath;	
}

void SPIPathMakerWidget::OnPathObjectChanged(const FAssetData& assetData) const
{
	UObject* object = assetData.GetAsset();

	if (object != nullptr && !object->IsA<UPIPathData>())
	{
		object = nullptr;
	}

	GetEdMode()->SetTargetPath(Cast<UPIPathData>(object));
}

void SPIPathMakerWidget::Construct(const FArguments& inArgs)
{
	_thumbnailPool = MakeShareable(new FAssetThumbnailPool(24));
	
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5.f)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Select the Path to edit:")))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SObjectPropertyEntryBox)
				.AllowedClass(UPIPathData::StaticClass())
				.ObjectPath(this, &SPIPathMakerWidget::GetPathObject)
				.OnObjectChanged(this, &SPIPathMakerWidget::OnPathObjectChanged)
				.AllowClear(true)
				.DisplayThumbnail(true)
				.ThumbnailPool(_thumbnailPool)
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT(
					"N -> Insert new next to the mouse position;\n"
					"M -> Mark point position;\n"
					"G -> Grab point nearest to mouse;\n"
					"D -> Delete point nearest to mouse;\n"
					"F -> Focus on point;\n"
					"S -> Mark Dirty (Save);"
				)))
			]
			+ SVerticalBox::Slot()
			.Padding(0.f, 20.f, 0.f, 0.f)
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text_Lambda([this]()-> FText
				{
					return FText::FromString(InfoText);
				})
			]
		]
	];
}

FPIPathMakerEditor* SPIPathMakerWidget::GetEdMode()
{
	const FEditorModeID& id = FPIPathMakerEditor::EditorModeID;
	FEdMode* edMode = GLevelEditorModeTools().GetActiveMode(id);
	return static_cast<FPIPathMakerEditor*>(edMode);
}
