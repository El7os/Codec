// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CCombatComponent.generated.h"

UCLASS()
class CDC_API UCCombatComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	friend class ACamp;

public:

	virtual void Activate(bool bReset) override;

	/**
	* Changes the current slot to Target slot if the target slot and the current slot aren't same or it isn't in between the weapon slot boundaries.
	* @param TargetSlot Indicates the slot that is wanted to be selected.
	* @return Returns true if the operation is done successfully, otherwise false.
	*/
	UFUNCTION(BlueprintCallable)
	bool ChangeSlot(int32 TargetSlot);

	/**
	* Assigns a weapon to the slot that indicated by TargetSlotIndex. If operations are successflly performed, one of these pipelines will fired according to 
	* the various situations. If Weapon is wanted to be assigned to an empty slot, its Init() function will be fired. After this OnSelected() function may be fired if
	* the slot that indicated by TargetSlotIndex is already selected, otherwise operation ends.
	*/
	UFUNCTION(BlueprintCallable)
	bool AssignWeaponToSlot(class AWeapon* const Weapon, int32 TargetSlotIndex, bool bRemoveExistingWeaponAtTargetSlot = false, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	bool RemoveWeaponAtTargetSlot(int32 TargetSlot);

	bool RemoveWeapon(class AWeapon* const Weapon);

	UFUNCTION(BlueprintCallable)
	int32 CreateSlot(int32 SlotCount = 1);

	UFUNCTION(BlueprintCallable)
	int32 GetFirstEmptySlotIndex();

	UFUNCTION(BlueprintCallable)
	void AddWeaponByID(int32 WeaponID, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	void AddWeaponByClass(UClass* const Class, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetSlotSize() const { return WeaponSlots.Num(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE class AWeapon* const GetCurrentWeapon() const { return GetCurrentWeapon_Internal(); };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetCurrentSlotIndex() { return CurrentSlotID; }

private:

	AWeapon* GetCurrentWeapon_Internal() const;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TArray<class AWeapon*> WeaponSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = "0"))
		int32 InitialSlotSize = 0;

	UPROPERTY()
		int32 CurrentSlotID = 0;
};
