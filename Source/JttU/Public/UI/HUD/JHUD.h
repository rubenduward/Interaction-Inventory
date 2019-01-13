// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHUD.generated.h"

class UJInventoryWidget;

/**
 *
 */
UCLASS()
class JTTU_API AJHUD : public AHUD
{
	GENERATED_BODY()

public:
	AJHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widgets")
	UJInventoryWidget* WBP_Inventory;

};
