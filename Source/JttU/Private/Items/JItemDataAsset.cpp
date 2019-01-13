// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JItemDataAsset.h"

#include "JBaseItem.h"

#include "UObject/ConstructorHelpers.h"


UJItemData::UJItemData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemName = TEXT("This item has no name");
	ItemDescription = TEXT("This item has no description");

	static ConstructorHelpers::FObjectFinder<UTexture2D> ItemIconRef(TEXT("Texture2D'/Game/JttU/Textures/UI/Inventory/T_Placeholder.T_Placeholder'"));
	if (ItemIconRef.Object)
	{
		ItemIcon = ItemIconRef.Object;
	}

	BaseItem = UJBaseItem::StaticClass();

	bIsReusable = false;
	ReuseCount = -1;
}
