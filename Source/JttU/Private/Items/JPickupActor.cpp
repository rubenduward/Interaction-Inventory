// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JPickupActor.h"

#include "JBaseItem.h"
#include "JInventoryComponent.h"
#include "JItemDataAsset.h"
#include "JCharacter.h"

#include "Components/StaticMeshComponent.h"


AJPickupActor::AJPickupActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	BaseItem = nullptr;
}

void AJPickupActor::BeginPlay()
{
	Super::BeginPlay();

}

void AJPickupActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AJPickupActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpawnBaseItem();
	LoadStaticMesh();
}

void AJPickupActor::SpawnBaseItem()
{
	if (ItemAsset.IsValid())
	{
		BaseItem = UJInventoryComponent::SpawnBaseItemStatic(ItemAsset, this, false);
	}
}

void AJPickupActor::LoadStaticMesh()
{
	if (BaseItem)
	{
		UJItemData* ItemData = BaseItem->GetItemData();
		UStaticMesh* StaticMesh = ItemData->StaticMesh.LoadSynchronous();
		if (StaticMesh)
		{
			GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
		}
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
