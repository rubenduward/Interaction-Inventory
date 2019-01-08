// Fill out your copyright notice in the Description page of Project Settings.

#include "JInventoryComponent.h"


UJInventoryComponent::UJInventoryComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UJInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	

}