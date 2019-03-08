// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JItemUsingWidget.h"

#include "JBaseItem.h"
#include "JItemDataAsset.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Image.h"

UJItemUsingWidget::UJItemUsingWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UJItemUsingWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UJItemUsingWidget::Setup(UJBaseItem* BaseItem)
{
	if (!BaseItem) return;

	Item = BaseItem;
	UJItemData* ItemData = Item->GetItemData();

	AsyncLoadIcon(ItemData->ItemIcon, Image_ItemIcon);
}

void UJItemUsingWidget::AsyncLoadIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget)
{
	if (!TargetWidget) return;

	if (Icon.IsValid())
	{
		SetIcon(Icon.Get(), TargetWidget);
		return;
	}

	TargetWidget->SetVisibility(ESlateVisibility::Hidden);

	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	check(AssetManager);

	FStreamableManager& Streamable = AssetManager->GetStreamableManager();
	Streamable.RequestAsyncLoad(Icon.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UJItemUsingWidget::SetIcon, Icon, TargetWidget), FStreamableManager::AsyncLoadHighPriority, false, false);
}

void UJItemUsingWidget::SetIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget)
{
	TargetWidget->SetBrushFromTexture(Icon.Get(), false);
	TargetWidget->SetVisibility(ESlateVisibility::Visible);
}