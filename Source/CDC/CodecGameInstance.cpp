// Fill out your copyright notice in the Description page of Project Settings.


#include "CodecGameInstance.h"

#include "CDC/Weapons/Weapon.h"
#include "CDC/Data/Weapon/DataAssets/WeaponDataAsset.h"
#include "CDC/Characters/CPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CDC/Components/CCombatComponent.h"


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

void UCodecGameInstance::AddWeaponByID(int32 ID, bool bForceToSelect)
{
	if (ACPlayerCharacter* const PlayerChar = Cast<ACPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (UCCombatComponent* const CombatComp = PlayerChar->FindComponentByClass<UCCombatComponent>())
			CombatComp->AddWeaponByID(ID, bForceToSelect);
	}
}

void UCodecGameInstance::AddWeaponToSlotByID(int32 ID, int32 TargetSlot,bool bRemoveExistingWeapon, bool bForceToSelect)
{
	if (ACPlayerCharacter* const PlayerChar = Cast<ACPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (UCCombatComponent* const CombatComp = PlayerChar->FindComponentByClass<UCCombatComponent>())
		{
			FTransform TargetTransform = FTransform(FVector(0.f,0.f,-100.f));
			if (AWeapon* Weapon = CreateWeapon(ID, TargetTransform))
				CombatComp->AssignWeaponToSlot(Weapon, TargetSlot, bRemoveExistingWeapon, bForceToSelect);
		}
	}
}

void UCodecGameInstance::AddSlot(int32 SlotCount)
{
	if (ACPlayerCharacter* const PlayerChar = Cast<ACPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (UCCombatComponent* const CombatComp = PlayerChar->FindComponentByClass<UCCombatComponent>())
		{
			CombatComp->CreateSlot(SlotCount);
		}
	}
}
