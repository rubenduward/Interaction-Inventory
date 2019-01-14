// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JInventoryItemTooltip.generated.h"

class UJItemData;

class UTextBlock;

/**
 * 
 */
UCLASS()
class JTTU_API UJInventoryItemTooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UJInventoryItemTooltip(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UTextBlock* Text_Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UTextBlock* Text_Description;

protected:
	virtual void NativeConstruct() override;

public:
	void Setup(UJItemData* ItemData);

};
