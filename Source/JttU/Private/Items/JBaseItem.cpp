// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JBaseItem.h"

#include "JInventoryComponent.h"
#include "JItemDataAsset.h"

#include "Engine/AssetManager.h"

UJBaseItem::UJBaseItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UJItemData* UJBaseItem::GetItemData() const
{
	return ItemData;
}
