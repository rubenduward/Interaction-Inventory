// Fill out your copyright notice in the Description page of Project Settings.

#include "JInventoryWidget.h"

#include "JCharacter.h"
#include "JBaseItem.h"
#include "JInventoryComponent.h"
#include "JInventoryItemGrid.h"
#include "JInventoryItemWidget.h"

#include "UObject/ConstructorHelpers.h"


UJInventoryWidget::UJInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UJInventoryItemWidget> ItemWidgetBP(TEXT("/Game/JttU/Blueprints/UI/Widgets/Inventory/WBP_ItemWidget"));
	ItemWidgetClass = ItemWidgetBP.Class;
}

void UJInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(ItemWidgetClass);
}

void UJInventoryWidget::Reconstruct()
{
	AJCharacter* Character = Cast<AJCharacter>(GetOwningPlayerPawn());
	check(Character);

	UJInventoryComponent* InventoryComponent = Character->GetInventoryComponent();
	TArray<UJBaseItem*> InventoryItems = InventoryComponent->GetInventoryItems();
	int MaxItems = InventoryComponent->MaxItems;
	
	for (int i = 0; i <= MaxItems; i++)
	{
		UJBaseItem* BaseItem = InventoryItems[i];

		UJInventoryItemWidget* ItemWidget = CreateWidget<UJInventoryItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		ItemWidget->Setup(BaseItem);
		WBP_ItemGrid->AddItemToGrid(ItemWidget, i);
	}
}
