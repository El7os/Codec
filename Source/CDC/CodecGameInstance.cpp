// Fill out your copyright notice in the Description page of Project Settings.


#include "CodecGameInstance.h"

#include "CDC/Weapons/Weapon.h"
#include "CDC/Data/Weapon/DataAssets/WeaponDataAsset.h"



AWeapon* UCodecGameInstance::CreateWeapon(int32 WeaponID, const FTransform& CustomTransformToSpawn)
{
	if (GetWorld())
	{
		if (UWeaponDataAsset** const WeaponDA = WeaponSet.Find(WeaponID))
		{
			if (UClass* const Class = (*WeaponDA)->GetClass())
			{
				return GetWorld()->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
			}
		}
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned, a weapon that associated with the ID(%i) cannot be found or OutWorldContext isn't valid."), WeaponID);
#endif

	return nullptr;
}

AWeapon* UCodecGameInstance::CreateWeapon(UClass* const Class, const FTransform& CustomTransformToSpawn)
{
	if (GetWorld() && Class)
		return GetWorld()->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned."));
#endif
	return nullptr;
}

AWeapon* UCodecGameInstance::BP_CreateWeaponByClass(UClass* const Class, UPARAM(ref) FTransform& CustomTransformToSpawn)
{
	if (GetWorld() && Class)
		return GetWorld()->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned"));
#endif
	return nullptr;
}

AWeapon* UCodecGameInstance::BP_CreateWeaponByID(int32 WeaponID, UPARAM(ref) FTransform& CustomTransformToSpawn)
{
	if (GetWorld())
	{
		if (UWeaponDataAsset** const WeaponDA = WeaponSet.Find(WeaponID))
		{
			if (UClass* const Class = (*WeaponDA)->GetClass())
			{
				return GetWorld()->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
			}
		}
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned, a weapon that associated with the ID(%i) cannot be found or OutWorldContext isn't valid."), WeaponID);
#endif
	return nullptr;
}

const UWeaponDataAsset* const UCodecGameInstance::GetWeaponDataByID(int WeaponID)
{
	return *WeaponSet.Find(WeaponID);
}

const UWeaponDataAsset* const UCodecGameInstance::GetWeaponDataByClass(UClass* const Class)
{
	if (Class)
	{
		for (const TTuple<int, UWeaponDataAsset*>& i : WeaponSet)
		{
			if (i.Value && i.Value->GetClass() == Class)
				return i.Value;
		}
	}

	return nullptr;
}