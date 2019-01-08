// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JBaseItem.generated.h"

/**
 * 
 */
UCLASS()
class JTTU_API UJBaseItem : public UObject
{
	GENERATED_BODY()
	
public:
	UJBaseItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bIsReusable : 1;
	
};
