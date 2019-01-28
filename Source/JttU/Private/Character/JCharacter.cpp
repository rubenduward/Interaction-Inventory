// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "JCharacter.h"

#include "JttU.h"
#include "JDoorActor.h"
#include "JInventoryComponent.h"
#include "JPlayerController.h"
#include "JUsableInterface.h"

#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/Material.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

//////////////////////////////////////////////////////////////////////////
// AJCharacter

AJCharacter::AJCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

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
	CursorToWorld->SetHiddenInGame(true);

	bMovementChangesDisabled = false;
	NearLocationRadius = 100.0f;
	MoveToDoorAcceptanceRadius = 100.0f;
	MoveToUsableAcceptanceRadius = 110.0f;
}

void AJCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateCursorLocation();
	UpdateFocusedUsableActor();
}

void AJCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("SetDestination", IE_Pressed, this, &AJCharacter::OnLeftClickPressed);
	PlayerInputComponent->BindAction("SetDestination", IE_Released, this, &AJCharacter::OnLeftClickReleased);
}

void AJCharacter::OnLeftClickPressed()
{
	AJPlayerController* PlayerController = Cast<AJPlayerController>(GetController());

	// Return early if movement changes are disabled, MoveToUsableActor is valid or we have started interacting with something.
	if (bMovementChangesDisabled)
	{
		PlayerController->OnSetDestinationReleased();
		return;
	}

	if (MoveToUsableActor)
	{
		MoveToUsableTimerCancel();
	}

	RemoveActionsWidget();
	if (!OnInteract())
	{
		PlayerController->OnSetDestinationPressed();
	}	
}

void AJCharacter::OnLeftClickReleased()
{
	AJPlayerController* PlayerController = Cast<AJPlayerController>(GetController());
	PlayerController->OnSetDestinationReleased();
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
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
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
			PlayerController->CurrentMouseCursor = EMouseCursor::Hand;
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
		PlayerController->CurrentMouseCursor = EMouseCursor::Default;
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

bool AJCharacter::OnInteract()
{
	if (!FocusedUsableActor) return false;
	if (MoveToUsableActor) return true;

	MoveToUsableActor = FocusedUsableActor;

	FVector Location = MoveToUsableActor->GetActorLocation();

	// Fire blueprint event to create and actions widget over the selected actor.
	CreateActionsWidget(MoveToUsableActor);
	return true;
}

void AJCharacter::MoveToUsableTimerStart()
{
	if (!MoveToUsableActor) return;

	FVector Location = MoveToUsableActor->GetActorLocation();
	// If we're navigating to a door, we need to find a nearby location.
	MoveToDestination = (MoveToUsableActor->IsA(AJDoorActor::StaticClass())) ? GetLocationNear(Location) : Location;

	GetWorldTimerManager().SetTimer(TimerHandle_MoveToUsable, this, &AJCharacter::MoveToUsable, 0.1f, true);
}

void AJCharacter::MoveToUsableTimerCancel()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_MoveToUsable);
	MoveToUsableActor = nullptr;
}

void AJCharacter::MoveToUsable()
{
	const float DistanceFrom = GetDistanceFromLocation(MoveToDestination);
	UE_LOG(LogTemp, Warning, TEXT("Distance to: %f"), DistanceFrom)

	const float AcceptanceRadius = (MoveToUsableActor->IsA(AJDoorActor::StaticClass())) ? MoveToDoorAcceptanceRadius : MoveToUsableAcceptanceRadius;
	if (DistanceFrom <= AcceptanceRadius)
	{
		MoveToUsableComplete();
	}

	AJPlayerController* PlayerController = Cast<AJPlayerController>(GetController());
	PlayerController->SetNewMoveDestination(MoveToDestination, false);
}

void AJCharacter::MoveToUsableComplete()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_MoveToUsable);

	AJPlayerController* PlayerController = Cast<AJPlayerController>(GetController());
	FVector DirectionVector = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), MoveToUsableActor->GetActorLocation());

	FRotator NewRotation(0.0f, DirectionVector.Rotation().Yaw, 0.0f);
	SetActorRotation(NewRotation);

	FName Action = NAME_None;
	IJUsableInterface::Execute_Interact(MoveToUsableActor, this, Action);

	MoveToUsableActor = nullptr;
	RemoveActionsWidget();
}

float AJCharacter::GetDistanceFromLocation(const FVector TargetLocation) const
{
	FVector MyLocation = GetActorLocation();
	FVector MyLocation2D(MyLocation.X, MyLocation.Y, 0.0f);

	FVector OtherActorLocation2D(TargetLocation.X, TargetLocation.Y, 0.0f);

	return (MyLocation2D - OtherActorLocation2D).Size();
}

FVector AJCharacter::GetLocationNear(const FVector TargetLocation) const
{
	FVector DirectionVector = UKismetMathLibrary::GetDirectionUnitVector(TargetLocation, GetActorLocation());
	return TargetLocation + (DirectionVector * NearLocationRadius);
}

void AJCharacter::DisableMovement(const bool bDisableMovement)
{
	bMovementChangesDisabled = bDisableMovement;
}

bool AJCharacter::IsMovementDisabled() const
{
	return bMovementChangesDisabled;
}
