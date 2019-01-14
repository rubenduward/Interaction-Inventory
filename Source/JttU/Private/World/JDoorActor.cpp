// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JDoorActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"


AJDoorActor::AJDoorActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	bOpen = bLocked = false;
	bHingeLeft = false;
}

void AJDoorActor::Open()
{
	if (bLocked) return;
	bOpen = true;
	K2_AnimateDoor();
}

void AJDoorActor::Close()
{
	bOpen = false;
	K2_AnimateDoor();
}

void AJDoorActor::SetLock(const bool bLock)
{
	bLocked = bLock;
}

void AJDoorActor::Activate()
{
	if (bLocked) return;
	bOpen = !bOpen;
	K2_AnimateDoor();
}

void AJDoorActor::DoorDriverUpdate(float Alpha)
{
	EndRotation = bHingeLeft ? FRotator(0.0f, 90.0f, 0.0f) : FRotator(0.0f, -90.0f, 0.0f);
	FRotator LerpRoation = UKismetMathLibrary::RLerp(StartRotation, EndRotation, Alpha, false);
	StaticMeshComp->SetRelativeRotation(LerpRoation);
}

bool AJDoorActor::Interact_Implementation(APawn* InstigatorPawn, FName Action)
{
	if (bLocked) return false;
	bOpen = !bOpen;
	K2_AnimateDoor();

	return true;
}
