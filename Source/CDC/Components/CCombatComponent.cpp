// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Components/CCombatComponent.h"

#include "CDC/CodecGameInstance.h"
#include "CDC/Weapons/Weapon.h"


void UCCombatComponent::Activate(bool bReset)
{
	if (/*!bReset &&*/ InitialSlotSize)
		WeaponSlots.AddDefaulted(InitialSlotSize);

}

bool UCCombatComponent::ChangeSlot(int32 TargetSlot)
{
	if (TargetSlot == CurrentSlotID) return true;
	if (GetSlotSize() && TargetSlot >= 0 && GetSlotSize() > TargetSlot)
	{
		if (GetCurrentWeapon_Internal())
			GetCurrentWeapon_Internal()->OnUnselected(UnselectReason::UnSelectReason_Swap);

		CurrentSlotID = TargetSlot;
		if (GetCurrentWeapon_Internal())
			GetCurrentWeapon_Internal()->OnSelected();
		return true;
	}
	return false;
}

bool UCCombatComponent::AssignWeaponToSlot(AWeapon* const Weapon, int32 TargetSlotIndex, bool bRemoveExistingWeaponAtTargetSlot, bool bForceToSelect)
{
	if (!Weapon || TargetSlotIndex < 0) return false;
	if (GetSlotSize() && GetSlotSize() > TargetSlotIndex && TargetSlotIndex >= 0)
	{
		if (WeaponSlots[TargetSlotIndex])
		{
			if (!bRemoveExistingWeaponAtTargetSlot) return false;
			if (CurrentSlotID == TargetSlotIndex)
				WeaponSlots[TargetSlotIndex]->OnUnselected(UnselectReason::UnSelectReason_Replace);
			WeaponSlots[TargetSlotIndex]->Destroy();
		}
		WeaponSlots[TargetSlotIndex] = Weapon;
		WeaponSlots[TargetSlotIndex]->Init(this);

		if (CurrentSlotID == TargetSlotIndex)
			WeaponSlots[TargetSlotIndex]->OnSelected();
		else if (bForceToSelect)
			ChangeSlot(TargetSlotIndex);
		return true;
	}
	return false;
}

bool UCCombatComponent::RemoveWeaponAtTargetSlot(int32 TargetSlot)
{
	if (GetSlotSize() && GetSlotSize() > TargetSlot && TargetSlot >= 0)
	{
		if (WeaponSlots[TargetSlot])
		{
			if (CurrentSlotID == TargetSlot)
				WeaponSlots[TargetSlot]->OnUnselected(UnselectReason::UnSelectReason_Replace);
			WeaponSlots[TargetSlot]->Destroy();
			WeaponSlots[TargetSlot] = nullptr;
			return true;
		}
	}
	return false;
}

bool UCCombatComponent::RemoveWeapon(AWeapon* const Weapon)
{
	if (Weapon)
	{
		int32 Size = GetSlotSize();
		for (int32 i = 0; i < Size; i++)
		{
			if (WeaponSlots[i] == Weapon)
			{
				if (i == CurrentSlotID)
					Weapon->OnUnselected(UnselectReason::UnSelectReason_Replace);
				Weapon->Destroy();
				WeaponSlots[i] = nullptr;
			}
		}
	}

	return false;
}

int32 UCCombatComponent::CreateSlot(int32 SlotCount)
{
	return WeaponSlots.AddDefaulted(SlotCount);
}

void UCCombatComponent::AddWeaponByID(int32 WeaponID, bool bForceToSelect)
{
	if (UCodecGameInstance* const GameInst = Cast<UCodecGameInstance>(GetOwner()->GetGameInstance()))
	{
		FTransform SpawnLocation = FTransform(FVector(0.0f, 0.0f, -100.f));
		if (AWeapon* const Weapon = GameInst->CreateWeapon(WeaponID, SpawnLocation))
			GetFirstEmptySlotIndex() >= 0 ? AssignWeaponToSlot(Weapon, GetFirstEmptySlotIndex(), false, bForceToSelect) : AssignWeaponToSlot(Weapon, CreateSlot(), false, bForceToSelect);
	}
}

void UCCombatComponent::AddWeaponByClass(UClass* const Class, bool bForceToSelect)
{
	if (!Class) return;

	if (UCodecGameInstance* const GameInst = Cast<UCodecGameInstance>(GetOwner()->GetGameInstance()))
	{
		FTransform SpawnLocation = FTransform(FVector(0.0f, 0.0f, -100.f));
		if (AWeapon* const Weapon = GameInst->CreateWeapon(Class, SpawnLocation))
			GetFirstEmptySlotIndex() >= 0 ? AssignWeaponToSlot(Weapon, GetFirstEmptySlotIndex(), false, bForceToSelect) : AssignWeaponToSlot(Weapon, CreateSlot(), false, bForceToSelect);
	}
}

int32 UCCombatComponent::GetFirstEmptySlotIndex()
{
	int32 Size = GetSlotSize();
	for (int i = 0; i < Size; i++)
	{
		if (!WeaponSlots[i])
			return i;
	}
	return -1;
}

AWeapon* UCCombatComponent::GetCurrentWeapon_Internal() const
{
	if (GetSlotSize())
		return WeaponSlots[CurrentSlotID];
	return nullptr;
}