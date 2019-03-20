// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JInspectActor.generated.h"

class UPointLightComponent;
class USceneCaptureComponent2D;
class USceneComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class JTTU_API AJInspectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AJInspectActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	FVector CurrentMeshExtent;

	UPROPERTY()
	FVector DesiredExtent;

	UPROPERTY()
	FVector DefaultDesiredExtent;

	UPROPERTY()
	FVector2D OnStartRotateLocation;

	UPROPERTY()
	uint8 bRotationEnabled : 1;

public:
	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void UpdateScale();

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void OnClickedStart(FVector2D MouseLocation);

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void OnClickedEnd(FVector2D MouseLocation);

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void OnMouseMove(FVector2D MouseLocation);

	UFUNCTION(BlueprintCallable, Category = "Inspect")
	void UpdateMesh(UStaticMesh* NewStaticMesh, float ZoomLevel);

};
