// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Components/CCombatComponent.h"

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
		AWeapon* SlotWeapon = WeaponSlots[TargetSlotIndex];
		if (SlotWeapon)
		{
			if (!bRemoveExistingWeaponAtTargetSlot) return false;
			if (CurrentSlotID == TargetSlotIndex)
				SlotWeapon->OnUnselected(UnselectReason::UnSelectReason_Replace);
			SlotWeapon->Destroy();
		}
		SlotWeapon = Weapon;
		SlotWeapon->Init(this);

		if (CurrentSlotID == TargetSlotIndex)
			SlotWeapon->OnSelected();
		else if (bForceToSelect)
			ChangeSlot(TargetSlotIndex);
		return true;
	}
	return false;
}

bool UCCombatComponent::AppendAndAssignWeapon(AWeapon* const Weapon, bool bCreateSlotToAdd, bool bForceToSelect)
{
	return false;
}

bool UCCombatComponent::RemoveWeapon(int32 TargetSlot)
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


AWeapon* const UCCombatComponent::GetCurrentWeapon_Internal()
{
	if (GetSlotSize())
		return WeaponSlots[CurrentSlotID];
	return nullptr;
}