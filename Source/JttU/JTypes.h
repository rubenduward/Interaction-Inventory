// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"

#include "JTypes.generated.h"

class UJBaseItem;
class AJPickupActor;

class UTexture2D;

//////////////////////////////////////////////////////////
// Inventory item types
//////////////////////////////////////////////////////////

USTRUCT()
struct FInventoryItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Required")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Required")
	FString ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Required")
	UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<UJBaseItem> BaseItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<AJPickupActor> PickupActor;

	uint8 bIsActive : 1;

	FInventoryItemData()
	{
		ItemName = TEXT("This item has no name");
		ItemDescription = TEXT("This item has no description");
		bIsActive = false;
	}
};