// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JUsableActor.h"
#include "JDoorActor.generated.h"

class USoundCue;

UCLASS()
class JTTU_API AJDoorActor : public AJUsableActor
{
	GENERATED_BODY()
	
public:	
	AJDoorActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	USoundCue* SoundOpen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	USoundCue* SoundClose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FRotator StartRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FRotator EndRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	uint8 bOpen : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	uint8 bLocked : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	uint8 bHingeLeft : 1;

protected:
	UFUNCTION(BlueprintCallable, Category = "Door")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void Close();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Door")
	void K2_AnimateDoor();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void DoorDriverUpdate(float Alpha);

public:
	// Public activation function used with switches
	void Activate();

public:
	// Usable Interface
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;
	
};
