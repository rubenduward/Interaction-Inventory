// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JInventoryWidget.generated.h"

class UJInventoryItemWidget;
class UJInventoryItemGrid;

class UWidgetSwitcher;

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class JTTU_API UJInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJInventoryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UJInventoryItemGrid* WBP_ItemGrid;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void Reconstruct();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<UJInventoryItemWidget> ItemWidgetClass;

};
