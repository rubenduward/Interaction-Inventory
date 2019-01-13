// Fill out your copyright notice in the Description page of Project Settings.

#include "JInventoryItemGrid.h"

#include "JInventoryItemWidget.h"
#include "JInventoryWidget.h"

#include "GridPanel.h"
#include "GridSlot.h"
#include "UniformGridPanel.h"
#include "UObject/ConstructorHelpers.h"


UJInventoryItemGrid::UJInventoryItemGrid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RowLength = 5;
}

void UJInventoryItemGrid::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJInventoryItemGrid::ClearItemGrid()
{
	Grid_ItemGrid->ClearChildren();
}

UGridSlot* UJInventoryItemGrid::AddItemToGrid(UWidget* Widget, int ItemIndex)
{
	check(Widget);

	UGridSlot* ItemSlot;
	ItemSlot = Grid_ItemGrid->AddChildToGrid(Widget);

	check(ItemSlot);

	SetGridColumn(ItemSlot, ItemIndex);
	SetGridRow(ItemSlot, ItemIndex);

	return ItemSlot;

	//int32 Children = Grid_ItemGrid->GetChildrenCount();

	//TSubclassOf<UGInventoryItemWidget> ItemWidgetClass;
	//// Check if we need to load the storage class or not
	//if (ItemWidget.Get())
	//{
	//	ItemWidgetClass = ItemWidget.Get();
	//}
	//else
	//{
	//	ItemWidgetClass = ItemWidget.LoadSynchronous();
	//}

	//check(ItemWidgetClass);
	//UGInventoryItemWidget* InventoryWidget = Cast<UGInventoryItemWidget>(CreateWidget(GetOwningPlayer(), ItemWidgetClass));
	//InventoryWidget->Setup();

	// UUniformGridSlot* GridItem = 
	// GridItem->SetColumn(0);
	// GridItem->SetRow(Children);
}

void UJInventoryItemGrid::SetGridColumn(UGridSlot* ItemSlot, int ItemIndex)
{
	int32 Column = ItemIndex % RowLength;
	ItemSlot->SetColumn(Column);
}

void UJInventoryItemGrid::SetGridRow(UGridSlot* ItemSlot, int ItemIndex)
{
	int32 Row = ItemIndex / RowLength;
	ItemSlot->SetRow(Row);
}
