// Fill out your copyright notice in the Description page of Project Settings.

#include "JInventoryComponent.h"

#include "JBaseItem.h"


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