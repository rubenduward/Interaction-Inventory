// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JInventoryComponent.h"

#include "JBaseItem.h"
#include "JItemDataAsset.h"

#include "Engine/AssetManager.h"


UJInventoryComponent::UJInventoryComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxItems = 20;
}

void UJInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Adding an element to the array
bool UJInventoryComponent::AddItem(UJBaseItem* BaseItem)
{
	if (InventoryItems.Num() >= MaxItems)
	{
		return false;
	}

	InventoryItems.Add(BaseItem);

	return true;
}

// Removing an element from the array
bool UJInventoryComponent::RemoveItem(UJBaseItem* BaseItem)
{
	for (int32 ItemIndex = 0; ItemIndex < InventoryItems.Num(); ItemIndex++)
	{
		if (InventoryItems[ItemIndex] == BaseItem)
		{
			InventoryItems.RemoveAt(ItemIndex);

			return true;
		}
	}

	return false;
}

TArray<UJBaseItem*> UJInventoryComponent::GetInventoryItems() const
{
	TArray<UJBaseItem*> ValidItems;
	for (auto& Item : InventoryItems)
	{
		if (Item && !Item->IsPendingKill())
		{
			ValidItems.Add(Item);
		}
	}

	return ValidItems;
}

UJBaseItem* UJInventoryComponent::SpawnBaseItemStatic(const FPrimaryAssetId& ItemAssetId, UObject* Owner, bool bAdd)
{
	if (!Owner) return nullptr;

	UAssetManager* AssetManager = UAssetManager::GetIfValid();
	check(AssetManager);

	UJItemData* ItemData = Cast<UJItemData>(AssetManager->GetPrimaryAssetObject(ItemAssetId));

	// Check if item data is loaded.
	if (!ItemData)
	{
		// Fetch Handle of Loading a Primary Asset
		TSharedPtr<FStreamableHandle> Handle = AssetManager->LoadPrimaryAsset(ItemAssetId, TArray<FName>(), FStreamableDelegate(), 100);

		// Invalid FPrimaryAssetId?
		if (!Handle.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("UJInventoryComponent::SpawnBaseItem() - Invalid Handle Spawning %s"), *ItemAssetId.ToString());
			return nullptr;
		}

		// TODO: Async
		Handle->WaitUntilComplete();

		// Check if the Asset was loaded successfully
		if (!Handle->HasLoadCompleted())
		{
			UE_LOG(LogTemp, Error, TEXT("UJInventoryComponent::SpawnBaseItem() - Failed to load primary asset."));
			return nullptr;
		}

		// Check if the Item data was loaded successfully
		ItemData = Cast<UJItemData>(Handle->GetLoadedAsset());
		if (!ItemData)
		{
			UE_LOG(LogTemp, Error, TEXT("UJInventoryComponent::SpawnBaseItem() - Failed to load asset data."));
			return nullptr;
		}
	}

	// TODO: Async Load in a Bundle
	UClass* ItemClass = ItemData->BaseItem.LoadSynchronous();

	UJBaseItem* Item = NewObject<UJBaseItem>(Owner, ItemClass);
	Item->AssetId = ItemAssetId;
	Item->ItemData = ItemData;

	// If the caller has requested to add it to this inventory we should add it
	if (bAdd)
	{
		if (UJInventoryComponent* TargetInventoryComp = Cast<UJInventoryComponent>(Owner))
		{
			TargetInventoryComp->AddItem(Item);
		}
	}

	return Item;
}

UJBaseItem* UJInventoryComponent::SpawnBaseItem(const FPrimaryAssetId& ItemAssetId, bool bAdd)
{
	return UJInventoryComponent::SpawnBaseItemStatic(ItemAssetId, this->GetOuter(), bAdd);
}
