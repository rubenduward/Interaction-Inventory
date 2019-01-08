// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "JUsableInterface.h"

#include "JUsableActor.generated.h"

UCLASS()
class JTTU_API AJUsableActor : public AActor, public IJUsableInterface
{
	GENERATED_BODY()
	
public:	
	AJUsableActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

protected:
	virtual void BeginPlay() override;

public:
	// Usable Interface
	void OnBeginFocus_Implementation(APawn* InstigatorPawn) override;
	void OnEndFocus_Implementation(APawn* InstigatorPawn) override;
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;

public:
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComp; }

};
