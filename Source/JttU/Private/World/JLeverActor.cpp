// Fill out your copyright notice in the Description page of Project Settings.

#include "JLeverActor.h"

#include "JttU.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"


AJLeverActor::AJLeverActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Handle"));
	SkeletalMeshComp->SetCollisionResponseToChannel(ECollisionChannel::TRACE_USEABLE, ECollisionResponse::ECR_Block);
	SkeletalMeshComp->SetupAttachment(StaticMeshComp);

}

// Called when the game starts or when spawned
void AJLeverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJLeverActor::OnBeginFocus_Implementation(APawn* InstigatorPawn)
{
	StaticMeshComp->SetRenderCustomDepth(true);
	SkeletalMeshComp->SetRenderCustomDepth(true);
}

void AJLeverActor::OnEndFocus_Implementation(APawn* InstigatorPawn)
{
	StaticMeshComp->SetRenderCustomDepth(false);
	SkeletalMeshComp->SetRenderCustomDepth(false);
}

bool AJLeverActor::Interact_Implementation(APawn* InstigatorPawn, FName Action)
{
	return true;
}