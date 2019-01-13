// Fill out your copyright notice in the Description page of Project Settings.

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

};
