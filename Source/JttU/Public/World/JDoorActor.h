// Copyright 2019, KamikazeXeX. All rights reserverd.

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

	UPROPERTY(VisibleAnywhere, Category = "Door")
	FRotator StartRotation;

	UPROPERTY(VisibleAnywhere, Category = "Door")
	FRotator EndRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	uint8 bOpen : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	uint8 bLocked : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door")
	uint8 bHingeLeft : 1;

protected:
	UFUNCTION(BlueprintCallable, Category = "Door")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "Door")
	void SetLock(const bool bLock = false);

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
