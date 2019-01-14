// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JCharacter.h"

#include "JttU.h"
#include "JInventoryComponent.h"
#include "JUsableInterface.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AJCharacter

AJCharacter::AJCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	InventoryComponent = CreateDefaultSubobject<UJInventoryComponent>(TEXT("InventoryComponent"));
	AddOwnedComponent(InventoryComponent);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/JttU/Materials/Decals/Cursor/M_Cursor.M_Cursor'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AJCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCursorLocation();
	UpdateFocusedUsableActor();
}

void AJCharacter::UpdateCursorLocation()
{
	if (!CursorToWorld) return;

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector CursorFV = TraceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(TraceHitResult.Location);
		CursorToWorld->SetWorldRotation(CursorR);
	}
}

void AJCharacter::UpdateFocusedUsableActor()
{
	AActor* NextFocusedUsableActor = TraceForUsableActor();
	if (NextFocusedUsableActor)
	{
		if (NextFocusedUsableActor != FocusedUsableActor)
		{
			// End focus on old actor
			if (FocusedUsableActor)
			{
				IJUsableInterface::Execute_OnEndFocus(FocusedUsableActor, this);
			}

			// Change focused actor
			FocusedUsableActor = NextFocusedUsableActor;

			// Start focus on new actor
			IJUsableInterface::Execute_OnBeginFocus(FocusedUsableActor, this);
		}
	}
	else
	{
		// End Focus If Out Of Range
		if (FocusedUsableActor)
		{
			IJUsableInterface::Execute_OnEndFocus(FocusedUsableActor, this);
		}

		FocusedUsableActor = nullptr;
	}
}

AActor * AJCharacter::TraceForUsableActor()
{

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(TRACE_USABLE, true, TraceHitResult);

		if (AActor* HitActor = TraceHitResult.GetActor())
		{
			if (UKismetSystemLibrary::DoesImplementInterface(HitActor, UJUsableInterface::StaticClass()))
			{
				return HitActor;
			}
		}
	}

	return nullptr;
}
