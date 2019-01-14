// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JPlayerController.generated.h"

/**
 *
 */
UCLASS()
class JTTU_API AJPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint8 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;

public:
	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation, bool bConsiderDistance = false);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

};
