// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JItemInspect.h"

#include "JBaseItem.h"
#include "JCharacter.h"
#include "JHUD.h"
#include "JInspectActor.h"
#include "JItemDataAsset.h"
#include "JUtilitiesBPFunctionLib.h"

#include "GameFramework/PlayerController.h"


UJItemInspect::UJItemInspect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UJItemInspect::UpdateInspectActor(UJBaseItem* Item)
{
	UJItemData* ItemData = Item->GetItemData();
	if (!ItemData)
	{
		AJHUD* HUD = Cast<AJHUD>(GetOwningPlayer()->GetHUD());
		HUD->HideInspectWidget();
		return;
	}

	AJCharacter* PlayerCharacter = Cast<AJCharacter>(GetOwningPlayerPawn());
	bool bSuccess = false;

	FName Path = FName(*ItemData->StaticMesh.ToString());
	UStaticMesh* StaticMesh = UJUtilitiesBPFunctionLib::LoadStaticMeshFromPath(Path, bSuccess);
	if (!bSuccess || !StaticMesh)
	{
		AJHUD* HUD = Cast<AJHUD>(GetOwningPlayer()->GetHUD());
		HUD->HideInspectWidget();
		return;
	}

	PlayerCharacter->GetInspectActor()->UpdateMesh(StaticMesh);
}
