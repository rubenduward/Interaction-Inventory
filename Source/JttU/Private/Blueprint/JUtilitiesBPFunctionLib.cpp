// Copyright 2019, KamikazeXeX. All rights reserverd.

#include "JUtilitiesBPFunctionLib.h"

#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"


//Get Path
FName UJUtilitiesBPFunctionLib::GetObjPath(const UObject* Obj)
{
	if (!Obj)
	{
		return NAME_None;
	}

	FStringAssetReference ThePath = FStringAssetReference(Obj);

	if (!ThePath.IsValid()) return NAME_None;

	//The Class FString Name For This Object
	FString Str = Obj->GetClass()->GetDescription();

	Str += "'";
	Str += ThePath.ToString();
	Str += "'";

	return FName(*Str);
}

template <typename T>
T* UJUtilitiesBPFunctionLib::LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	return Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *Path.ToString()));
}

UStaticMesh* UJUtilitiesBPFunctionLib::LoadStaticMeshFromPath(const FName& Path, bool& bSuccess)
{
	bSuccess = false;
	if (Path == NAME_None) return nullptr;

	UStaticMesh* StaticMesh = LoadObjFromPath<UStaticMesh>(Path);
	if (!StaticMesh)
	{
		return nullptr;
	}

	bSuccess = true;
	return StaticMesh;
}
