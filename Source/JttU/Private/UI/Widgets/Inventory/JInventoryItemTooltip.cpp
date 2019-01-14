// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JInventoryItemTooltip.h"

#include "JItemDataAsset.h"

#include "TextBlock.h"

UJInventoryItemTooltip::UJInventoryItemTooltip(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UJInventoryItemTooltip::NativeConstruct()
{
	Super::NativeConstruct();

}

void UJInventoryItemTooltip::Setup(UJItemData* ItemData)
{
	if (!ItemData) return;

	Text_Name->SetText(FText::FromString(ItemData->ItemName));
	Text_Description->SetText(FText::FromString(ItemData->ItemDescription));
}