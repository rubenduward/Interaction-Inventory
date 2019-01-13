// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JInventoryItemWidget.generated.h"

class UJBaseItem;

class UBorder;
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
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UImage* Image_ItemIcon;

public:
	void Setup(UJBaseItem* BaseItem);

};
