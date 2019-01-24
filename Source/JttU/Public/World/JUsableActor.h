// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "JUsableInterface.h"

#include "JUsableActor.generated.h"

UCLASS()
class JTTU_API AJUsableActor : public AActor, public IJUsableInterface
{
	GENERATED_BODY()

public:
	AJUsableActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

	/** A component that will be hidden in game but is used to get the location for the action widgets */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ActionsPoint;

protected:
	virtual void BeginPlay() override;

public:
	// Usable Interface
	void OnBeginFocus_Implementation(APawn* InstigatorPawn) override;
	void OnEndFocus_Implementation(APawn* InstigatorPawn) override;
	bool Interact_Implementation(APawn* InstigatorPawn, FName Action) override;

public:
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector GetActionWidgetLocation() const { return ActionsPoint->GetComponentLocation(); }

};
