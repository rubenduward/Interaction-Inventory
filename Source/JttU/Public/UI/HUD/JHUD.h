// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHUD.generated.h"

class UJInventoryWidget;
class UJItemInspect;

class UUserWidget;

/**
 *
 */
UCLASS()
class JTTU_API AJHUD : public AHUD
{
	GENERATED_BODY()

public:
	AJHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UJInventoryWidget* WBP_Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* WBP_ActionsWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UUserWidget* WBP_ItemActions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UJItemInspect* WBP_ItemInspect;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	UUserWidget* ActiveWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void DisplayWidget(UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void CloseWidget(UUserWidget* Widget = nullptr);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void FocusWidget(UUserWidget* Widget = nullptr);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	bool IsWidgetOpen(UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, Category = "HUD")
	bool IsAnyWidgetOpen();

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ShowInventoryWidget();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HideInventoryWidget();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventoryWidget();

public:
	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void ShowInspectWidget(UJBaseItem* ItemContext);

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void HideInspectWidget();

public:
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ShowActionsWidget(FVector2D ScreenLocation);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void HideActionsWidget();

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsInventoryOpen() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool IsActionsWidgetShown() const;

};
