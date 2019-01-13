// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JItemDataAsset.generated.h"

class UJBaseItem;

class UTexture2D;
class USoundCue;
class UStaticMesh;

UCLASS(BlueprintType)
class JTTU_API UJItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UJItemData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/** Item's name. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Required")
	FString ItemName;

	/** Item's description. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Required")
	FString ItemDescription;

	/** Items inventory icon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cosmetic")
	TSoftObjectPtr<UTexture2D> ItemIcon;

	/** The base item class for this item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSoftClassPtr<UJBaseItem> BaseItem;

	/** The static mesh that represents this item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSoftObjectPtr<UStaticMesh> StaticMesh;

	/** Can this item be re-used? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	uint8 bIsReusable : 1;

	/** Total amount of times this item can be used. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	int ReuseCount;

	/** Current times this item has been used. */
	UPROPERTY(BlueprintReadOnly, Category = "General")
	int UseCount;

};
