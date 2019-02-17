// Copyright 2019, KamikazeXeX. All rights reserverd.

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
	ConstructorHelpers::FClassFinder<UJInventoryItemWidget> ItemWidgetBP(TEXT("/Game/JttU/Blueprints/UI/Widgets/Inventory/WBP_ItemWidget"));
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

	WBP_ItemGrid->ClearItemGrid();

	UJInventoryComponent* InventoryComponent = Character->GetInventoryComponent();
	TArray<UJBaseItem*> InventoryItems = InventoryComponent->GetInventoryItems();

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		UJBaseItem* BaseItem = InventoryItems[i];

		UJInventoryItemWidget* ItemWidget = CreateWidget<UJInventoryItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		ItemWidget->Setup(BaseItem);
		WBP_ItemGrid->AddItemToGrid(ItemWidget, i);
	}
}
