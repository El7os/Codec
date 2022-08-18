// Fill out your copyright notice in the Description page of Project Settings.


#include "CodecGameInstance.h"

#include "CDC/Weapons/Weapon.h"



AWeapon* UCodecGameInstance::CreateWeapon(UWorld* const OutWorldContext, int WeaponID, const FTransform& CustomTransformToSpawn)
{
	if (WorldContext && PlayerWeaponClasses.Num() > WeaponID && WeaponID >= 0)
	{
		return OutWorldContext->SpawnActor<AWeapon>(PlayerWeaponClasses[WeaponID], CustomTransformToSpawn);
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned (Weapon ID : %i)"), WeaponID);
#endif
	return nullptr;
}

AWeapon* UCodecGameInstance::CreateWeapon(UWorld* const OutWorldContext, UClass* const Class, const FTransform& CustomTransformToSpawn)
{
	if (WorldContext && Class)
	{
		return OutWorldContext->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned"));
#endif
	return nullptr;
}

AWeapon* UCodecGameInstance::BP_CreateWeaponByClass(UWorld* const OutWorldContext, UClass* const Class, UPARAM(ref) FTransform& CustomTransformToSpawn)
{
	if (WorldContext && Class)
	{
		return OutWorldContext->SpawnActor<AWeapon>(Class, CustomTransformToSpawn);
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned"));
#endif
	return nullptr;
}

AWeapon* UCodecGameInstance::BP_CreateWeaponByID(UWorld* const OutWorldContext, int WeaponID, UPARAM(ref) FTransform& CustomTransformToSpawn)
{
	if (WorldContext && PlayerWeaponClasses.Num() > WeaponID && WeaponID >= 0)
	{
		return OutWorldContext->SpawnActor<AWeapon>(PlayerWeaponClasses[WeaponID], CustomTransformToSpawn);
	}
#ifdef WITH_EDITOR
	else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned (Weapon ID : %i)"), WeaponID);
#endif
	return nullptr;
}