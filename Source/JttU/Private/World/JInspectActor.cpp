// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JInspectActor.h"

#include "Components/PointLightComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

AJInspectActor::AJInspectActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(Root);
	SceneCapture->SetRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));
	SceneCapture->FOVAngle = 60.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(Root);
	PointLight->SetRelativeLocation(FVector(0.0f, -60.0f, 110.0f));

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	DesiredExtent = FVector(18.0f, 18.0f, 18.0f);
	bRotationEnabled = false;
}

void AJInspectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJInspectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJInspectActor::UpdateScale()
{
	FVector Origin01;
	FVector BoxExtent01;
	float SphereRadius01;
	UKismetSystemLibrary::GetComponentBounds(StaticMeshComponent, Origin01, BoxExtent01, SphereRadius01);
	CurrentMeshExtent = BoxExtent01;

	FVector WorldScale = StaticMeshComponent->GetComponentScale();	
	float MinExtent = UKismetMathLibrary::GetMinElement(DesiredExtent / CurrentMeshExtent);
	FVector NewScale = WorldScale * MinExtent;
	StaticMeshComponent->SetWorldScale3D(NewScale);

	FVector Origin02;
	FVector BoxExtent02;
	float SphereRadius02;
	UKismetSystemLibrary::GetComponentBounds(StaticMeshComponent, Origin02, BoxExtent02, SphereRadius02);

	FVector DeltatLocation = StaticMeshComponent->GetComponentLocation() - Origin02;

	FHitResult HitResult;
	StaticMeshComponent->AddLocalOffset(DeltatLocation, false, &HitResult, ETeleportType::None);
}

void AJInspectActor::OnClickedStart(FVector2D MouseLocation)
{
	OnStartRotateLocation = MouseLocation;
	bRotationEnabled = true;
}

void AJInspectActor::OnClickedEnd(FVector2D MouseLocation)
{
	bRotationEnabled = false;
}

void AJInspectActor::OnMouseMove(FVector2D MouseLocation)
{
	if (!bRotationEnabled) return;

	FVector2D DeltaLocation = MouseLocation - OnStartRotateLocation;
	FRotator WorldRotation = FRotator(DeltaLocation.Y, DeltaLocation.X * -1, 0.0f);
	SceneComponent->AddWorldRotation(WorldRotation);

	OnStartRotateLocation = MouseLocation;
}

void AJInspectActor::UpdateMesh(UStaticMesh* NewStaticMesh)
{
	StaticMeshComponent->SetStaticMesh(NewStaticMesh);

	FHitResult HitResult;
	StaticMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f), false, &HitResult, ETeleportType::None);
	SceneComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	UpdateScale();
}
