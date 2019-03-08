// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JBaseItem.generated.h"

class UJItemData;

/**
 *
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class JTTU_API UJBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UJBaseItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(BlueprintReadOnly)
	FPrimaryAssetId AssetId;

	UPROPERTY()
	UJItemData* ItemData;

public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "ItemData")
	UJItemData* GetItemData() const;

};
