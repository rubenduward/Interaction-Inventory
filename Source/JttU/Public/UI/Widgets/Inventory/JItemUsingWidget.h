// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JItemUsingWidget.generated.h"

class UButton;
class UImage;

/**
 * 
 */
UCLASS()
class JTTU_API UJItemUsingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJItemUsingWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget = "true"))
	UImage* Image_ItemIcon;

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (ExposeOnSpawn))
	UJBaseItem* Item;

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Setup(UJBaseItem* BaseItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AsyncLoadIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget);
	virtual void SetIcon(TSoftObjectPtr<UTexture2D> Icon, UImage* TargetWidget);

};
