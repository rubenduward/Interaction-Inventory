// Fill out your copyright notice in the Description page of Project Settings.

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemRowName;

	UPROPERTY(BlueprintReadWrite, Category = "Item")
	UJBaseItem* BaseItem;

protected:
	virtual void BeginPlay() override;

public:
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;

};
