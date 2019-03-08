// Copyright 2019, KamikazeXeX. All rights reserverd.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/EngineBaseTypes.h"

#include "JUtilitiesBPFunctionLib.generated.h"

class UStaticMesh;

/**
 * 
 */
UCLASS()
class JTTU_API UJUtilitiesBPFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Get the path for any UObject. */
	static FName GetObjPath(const UObject* Obj);

	/** Loads any object type from path */
	template <typename T>
	static T* LoadObjFromPath(const FName& Path);

	/** Load Static Mesh From Path */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Load Static Mesh From Path", CompactNodeTitle = "LoadStaticMeshFromPath"), Category = "Load Static Mesh From Path")
	static UStaticMesh* LoadStaticMeshFromPath(const FName& Path, bool& bSuccess);
	
};
