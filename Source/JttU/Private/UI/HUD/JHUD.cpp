// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JHUD.h"

#include "JInventoryWidget.h"
#include "JItemInspect.h"

#include "UserWidget.h"
#include "WidgetBlueprintLibrary.h"

AJHUD::AJHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActiveWidget = nullptr;
}

void AJHUD::BeginPlay()
{
	Super::BeginPlay();

	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void AJHUD::DisplayWidget(UUserWidget* Widget)
{
	check(Widget);

	if (IsAnyWidgetOpen())
	{
		CloseWidget(ActiveWidget);
		return;
	}

	ActiveWidget = Widget;
	ActiveWidget->AddToViewport();
	FocusWidget(ActiveWidget);
}

void AJHUD::CloseWidget(UUserWidget* Widget)
{
	UUserWidget* TargetWidget = Widget ? Widget : ActiveWidget;
	if (TargetWidget)
	{
		TargetWidget->RemoveFromViewport();
		ActiveWidget = nullptr;
		FocusWidget();
	}
}

void AJHUD::FocusWidget(UUserWidget* Widget)
{
	const bool bValidWidget = (Widget != nullptr);
	APlayerController* const OwningPlayerController = GetOwningPlayerController();
	OwningPlayerController->SetCinematicMode(bValidWidget, true, true);
	//OwningPlayerController->bShowMouseCursor = bValidWidget;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);

	if (bValidWidget)
	{
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
	}
	else
	{
		InputMode.SetWidgetToFocus(nullptr);
	}

	OwningPlayerController->SetInputMode(InputMode);

	if (APawn* ControlledPawn = OwningPlayerController->GetPawn())
	{
		if (bValidWidget)
		{
			ControlledPawn->DisableInput(OwningPlayerController);
		}
		else
		{
			ControlledPawn->EnableInput(OwningPlayerController);
		}
	}
}

bool AJHUD::IsWidgetOpen(UUserWidget* Widget)
{
	if (Widget)
	{
		return (Widget == ActiveWidget);
	}

	return (ActiveWidget != nullptr);
}

bool AJHUD::IsAnyWidgetOpen()
{
	return (ActiveWidget != nullptr);
}

void AJHUD::ShowInspectWidget(UJBaseItem* ItemContext)
{
	if (!WBP_ItemInspect) return;
	if (WBP_ItemInspect->IsInViewport()) return;

	WBP_ItemInspect->UpdateInspectActor(ItemContext);

	WBP_ItemInspect->AddToViewport();

	APlayerController* const OwningPlayerController = GetOwningPlayerController();

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(WBP_ItemInspect->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	OwningPlayerController->SetInputMode(InputMode);
}

void AJHUD::HideInspectWidget()
{
	WBP_ItemInspect->RemoveFromParent();
	FocusWidget(WBP_Inventory);
}

void AJHUD::ShowActionsWidget(FVector2D ScreenLocation)
{
	if (!WBP_ActionsWidget) return;

	WBP_ActionsWidget->SetPositionInViewport(ScreenLocation);
	DisplayWidget(WBP_ActionsWidget);
}

void AJHUD::HideActionsWidget()
{
	if (!WBP_ActionsWidget) return;

	CloseWidget(WBP_ActionsWidget);
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

bool AJHUD::IsInventoryOpen() const
{
	if (!WBP_Inventory) return false;
	return WBP_Inventory->IsInViewport();
}