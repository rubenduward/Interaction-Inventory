// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JUsableActor.h"
#include "JLeverActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class JTTU_API AJLeverActor : public AJUsableActor
{
	GENERATED_BODY()
	
public:	
	AJLeverActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComp;

protected:
	virtual void BeginPlay() override;

public:
	// Usable Interface
	void OnBeginFocus_Implementation(APawn* InstigatorPawn) override;
	void OnEndFocus_Implementation(APawn* InstigatorPawn) override;
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;

public:
	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComp; }

};
