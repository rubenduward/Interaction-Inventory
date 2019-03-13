// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JPlayerController.h"

#include "JCharacter.h"
#include "JHUD.h"
#include "JInventoryWidget.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"

AJPlayerController::AJPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AJPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AJPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AJCharacter* MyPawn = Cast<AJCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AJPlayerController::SetNewMoveDestination(const FVector DestLocation, bool bConsiderDistance /*= false*/)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		if (bConsiderDistance)
		{
			// We need to issue move command only if far enough in order for walk animation to play correctly
			float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
			if (Distance < 120.0f) return;
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	}
}

void AJPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AJPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

bool AJPlayerController::IsInventoryOpen() const
{
	if (AJHUD* HUD = Cast<AJHUD>(GetHUD()))
	{
		return HUD->IsInventoryOpen();
	}

	return false;
}

bool AJPlayerController::IsActionsWidgetShown() const
{
	if (AJHUD* HUD = Cast<AJHUD>(GetHUD()))
	{
		return HUD->IsActionsWidgetShown();
	}

	return false;
}

