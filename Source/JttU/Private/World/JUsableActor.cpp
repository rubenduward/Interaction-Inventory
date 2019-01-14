// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JUsableActor.h"

#include "JttU.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"


AJUsableActor::AJUsableActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::TRACE_USABLE, ECollisionResponse::ECR_Block);
	StaticMeshComp->SetupAttachment(RootComponent);
}

void AJUsableActor::BeginPlay()
{
	Super::BeginPlay();
}

void AJUsableActor::OnBeginFocus_Implementation(APawn* InstigatorPawn)
{
	StaticMeshComp->SetRenderCustomDepth(true);
}

void AJUsableActor::OnEndFocus_Implementation(APawn* InstigatorPawn)
{
	StaticMeshComp->SetRenderCustomDepth(false);
}

bool AJUsableActor::Interact_Implementation(APawn* InstigatorPawn, FName Action)
{
	return true;
}
