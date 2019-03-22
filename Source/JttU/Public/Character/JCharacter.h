// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JCharacter.generated.h"

class AJInspectActor;
class UJBaseItem;
class UJInventoryComponent;

class UCameraComponent;
class UDecalComponent;
class UInputComponent;
class USpringArmComponent;

UCLASS(config=Game)
class JTTU_API AJCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* CursorToWorld;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UJInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inspect", meta = (AllowPrivateAccess = "true"))
	AJInspectActor* InspectActor;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	/** Updates the location of the material based cursor. */
	void UpdateCursorLocation();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnLeftClickPressed();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnLeftClickReleased();

protected:
	/** Client Use Input Key (F) */
	bool OnInteract();

	/** Will update the focused usable actor after first tracing for one. */
	void UpdateFocusedUsableActor();

	/** Traces for a usable actor under the mouse cursor. */
	UFUNCTION(BlueprintCallable, Category = "ObjectInteraction")
	AActor* TraceForUsableActor();

	/** The currently focused usable actor. */
	UPROPERTY()
	AActor* FocusedUsableActor;

	UPROPERTY(BlueprintReadWrite, Category = "Using")
	UJBaseItem* ItemUsing;

protected:
	/** Radius from doors character has to be within before completed event fires (centimeters). NOTE: Do not set to less than 50. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	float MoveToDoorAcceptanceRadius;

	/** Radius from objects character has to be within before completed event fires (centimeters). NOTE: Do not set to less than 50. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	float MoveToUsableAcceptanceRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	float NearLocationRadius;

	/** Move to a usable actor with a timer. */
	UFUNCTION(BlueprintCallable)
	void MoveToUsableTimerStart();
	void MoveToUsableTimerCancel();
	void MoveToUsable();
	void MoveToUsableComplete();

	UPROPERTY(Transient)
	FTimerHandle TimerHandle_MoveToUsable;

	UPROPERTY(Transient)
	AActor* MoveToUsableActor;

	UPROPERTY(Transient)
	FName MoveToAction;

	UPROPERTY(Transient)
	FVector MoveToDestination;

	float GetDistanceFromLocation(const FVector TargetLocation) const;
	FVector GetLocationNear(const FVector TargetLocation) const;

private:
	UPROPERTY()
	uint8 bMovementInputIgnored : 1;

public:
	UFUNCTION(BlueprintCallable)
	void IgnoreMovementInputs(bool bIgnoreMovementInputs = false);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsIgnoringMovementInputs() const;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateActionsWidget(const AActor* SelectedActor);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveActionsWidget();

public:
	/** Returns TopDownCameraComponent subobject **/
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "CameraComponent")
	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Camera")
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns CursorToWorld subobject. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "CursorToWorld")
	FORCEINLINE UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Returns the inventory component. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inventory")
	FORCEINLINE UJInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	/** Returns the InsepctActor. */
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inspect")
	FORCEINLINE AJInspectActor* GetInspectActor() const { return InspectActor; }

};
