// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JUsableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJUsableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class JTTU_API IJUsableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category = Interaction, meta = (DisplayName = "On Begin Focus"), BlueprintCosmetic)
	void OnBeginFocus(APawn* InstigatorPawn);

	UFUNCTION(BlueprintNativeEvent, Category = Interaction, meta = (DisplayName = "On End Focus"), BlueprintCosmetic)
	void OnEndFocus(APawn* InstigatorPawn);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interaction, meta = (DisplayName = "On Use"), BlueprintAuthorityOnly)
	bool Interact(APawn* InstigatorPawn, FName Action);
};
