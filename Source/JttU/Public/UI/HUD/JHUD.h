// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHUD.generated.h"

class UJInventoryWidget;

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

public:
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ShowActionsWidget(FVector2D ScreenLocation);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void HideActionsWidget();

};
