// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "JUsableActor.h"
#include "JPickupActor.generated.h"

class UJBaseItem;

/**
 * World representation for inventory items.
 */
UCLASS(Abstract)
class JTTU_API AJPickupActor : public AJUsableActor
{
	GENERATED_BODY()

public:
	AJPickupActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	void SpawnBaseItem();
	void LoadStaticMesh();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Item")
	UJBaseItem* BaseItem;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item")
	FPrimaryAssetId ItemAsset;

public:
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;

};
