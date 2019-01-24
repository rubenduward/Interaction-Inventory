// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JHUD.h"

#include "UserWidget.h"

AJHUD::AJHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AJHUD::ShowActionsWidget(FVector2D ScreenLocation)
{
	if (!WBP_ActionsWidget) return;

	WBP_ActionsWidget->SetPositionInViewport(ScreenLocation);
	WBP_ActionsWidget->AddToViewport();
}

void AJHUD::HideActionsWidget()
{
	if (!WBP_ActionsWidget) return;
	WBP_ActionsWidget->RemoveFromParent();
}
