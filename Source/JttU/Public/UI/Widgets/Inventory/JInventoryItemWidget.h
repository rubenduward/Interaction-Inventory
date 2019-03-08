// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JInventoryItemWidget.generated.h"

class UJBaseItem;
class UJInventoryItemTooltip;
class UJItemData;

class UButton;
class UImage;

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class JTTU_API UJInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJInventoryItemWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UButton* Button_Item;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UImage* Image_ItemIcon;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item")
	UJBaseItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<UJInventoryItemTooltip> TooltipWidgetClass;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Setup(UJBaseItem* BaseItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AsyncLoadIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget);
	virtual void SetIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inventory")
	UWidget* GetToolTipWidget();

};
