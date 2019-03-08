// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JItemInspect.generated.h"

class UJBaseItem;

/**
 * 
 */
UCLASS()
class JTTU_API UJItemInspect : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UJItemInspect(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void UpdateInspectActor(UJBaseItem* Item);
	
};
