// Fill out your copyright notice in the Description page of Project Settings.

#include "JPickupActor.h"

#include "JBaseItem.h"
#include "JInventoryComponent.h"
#include "JCharacter.h"


AJPickupActor::AJPickupActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	BaseItem = nullptr;
	ItemRowName = NAME_None;
}

void AJPickupActor::BeginPlay()
{
	Super::BeginPlay();

	if (ItemRowName != NAME_None)
	{
		// BaseItem = (UJBaseItem*)UJInventoryComponent::SpawnItemStatic(ItemRowName, this);
	}
}

bool AJPickupActor::Interact_Implementation(APawn* InstigatorPawn, FName Action)
{
	//if (AJCharacter* PlayerChar = Cast<AJCharacter>(InstigatorPawn))
	//{
	//	UJInventoryComponent* InventoryComponent = PlayerChar->GetInventoryComponent();
	//	if (PlayerChar->PickupFromGround(this))
	//	{
	//		if (BaseItem && !BaseItem->IsPendingKill())
	//		{
	//			BaseItem->ConditionalBeginDestroy();
	//			BaseItem = nullptr;
	//		}
	//		Destroy();
	//	}
	//}

	return true;
}
