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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class AWeapon* const GetCurrentWeapon() const { return GetCurrentWeapon_Internal(); };

	UFUNCTION(BlueprintCallable)
	bool ChangeSlot(int32 TargetSlot);

	UFUNCTION(BlueprintCallable)
	bool AssignWeaponToSlot(class AWeapon* const Weapon, int32 TargetSlotIndex, bool bRemoveExistingWeaponAtTargetSlot = false, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	bool AppendAndAssignWeapon(class AWeapon* const Weapon, bool bCreateSlotToAdd = false, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	bool RemoveWeaponAtTargetSlot(int32 TargetSlot);

	bool RemoveWeapon(class AWeapon* const Weapon);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetSlotSize() const { return WeaponSlots.Num(); }

	UFUNCTION(BlueprintCallable)
	int32 CreateSlot(int32 SlotCount = 1);

	virtual void Activate(bool bReset) override;

	UFUNCTION(BlueprintCallable)
	void AddWeaponByID(int32 WeaponID, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	void AddWeaponByClass(UClass* const Class, bool bForceToSelect = false);

	UFUNCTION(BlueprintCallable)
	int32 GetFirstEmptySlotIndex();

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
