// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JInventoryComponent.generated.h"

class UJBaseItem;

UCLASS(ClassGroup=(Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class JTTU_API UJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<UJBaseItem*> InventoryItems;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	int MaxItems;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UJBaseItem* BaseItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UJBaseItem* BaseItem);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inventory")
	TArray<UJBaseItem*> GetInventoryItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	static UJBaseItem* SpawnBaseItemStatic(const FPrimaryAssetId& ItemAssetId, UObject* Owner, bool bAdd = false);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UJBaseItem* SpawnBaseItem(const FPrimaryAssetId& ItemAssetId, bool bAdd);

};
