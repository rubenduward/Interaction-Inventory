// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JInventoryComponent.generated.h"

class UJBaseItem;

UCLASS(ClassGroup=(Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class JTTU_API UJInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJInventoryComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TArray<UJBaseItem*> InventoryItems;

};
