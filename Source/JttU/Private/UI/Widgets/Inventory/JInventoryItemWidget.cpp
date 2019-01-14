// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JInventoryItemWidget.h"

#include "JBaseItem.h"
#include "JInventoryItemTooltip.h"
#include "JItemDataAsset.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Image.h"


UJInventoryItemWidget::UJInventoryItemWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ToolTipWidgetDelegate.BindUFunction(this, FName(TEXT("GetToolTipWidget")));

}

void UJInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(TooltipWidgetClass);

}

void UJInventoryItemWidget::Setup(UJBaseItem* BaseItem)
{
	if (!BaseItem) return;

	Item = BaseItem;
	UJItemData* ItemData = Item->GetItemData();

	AsyncLoadIcon(ItemData->ItemIcon, Image_ItemIcon);
}

void UJInventoryItemWidget::AsyncLoadIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget)
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
	Streamable.RequestAsyncLoad(Icon.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &UJInventoryItemWidget::SetIcon, Icon, TargetWidget), FStreamableManager::AsyncLoadHighPriority, false, false);
}

void UJInventoryItemWidget::SetIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget)
{
	TargetWidget->SetBrushFromTexture(Icon.Get(), false);
	TargetWidget->SetVisibility(ESlateVisibility::Visible);
}

UWidget* UJInventoryItemWidget::GetToolTipWidget()
{
	if (!Item) return nullptr;

	UJItemData* ItemData = Item->GetItemData();
	if (!ItemData) return nullptr;

	UJInventoryItemTooltip* TooltipWidget = CreateWidget<UJInventoryItemTooltip>(GetOwningPlayer(), TooltipWidgetClass);
	TooltipWidget->Setup(ItemData);

	return TooltipWidget;
}
