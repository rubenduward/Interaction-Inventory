// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JInventoryItemGrid.generated.h"

class UGridPanel;
class UGridSlot;
class UUniformGridPanel;

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class JTTU_API UJInventoryItemGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UJInventoryItemGrid(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UGridPanel* Grid_ItemGrid;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	int RowLength;

public:
	UFUNCTION(BlueprintCallable)
	void ClearItemGrid();

	UFUNCTION(BlueprintCallable)
	UGridSlot* AddItemToGrid(UWidget* Widget, int ItemIndex);

	UFUNCTION(BlueprintCallable)
	void SetGridColumn(UGridSlot* ItemSlot, int ItemIndex);

	UFUNCTION(BlueprintCallable)
	void SetGridRow(UGridSlot* ItemSlot, int ItemIndex);

};
