// Fill out your copyright notice in the Description page of Project Settings.

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
	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::TRACE_USEABLE, ECollisionResponse::ECR_Block);
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