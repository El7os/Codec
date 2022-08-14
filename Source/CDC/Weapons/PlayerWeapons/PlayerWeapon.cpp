// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Weapons/PlayerWeapons/PlayerWeapon.h"

#include "CDC/Components/CCombatComponent.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"


APlayerWeapon::APlayerWeapon() : AWeapon()
{
}

void APlayerWeapon::Init(UCCombatComponent* CombatComponent)
{
	Super::Init(CombatComponent);

	
}

void APlayerWeapon::OnSelected()
{
	Super::OnSelected();

	if (Component)
	{
		PrimaryAbilitySpecHandle = Component->GiveAbility(FGameplayAbilitySpec(PrimaryAbilityClass, 1, -1, this));
		SecondaryAbilitySpecHandle = Component->GiveAbility(FGameplayAbilitySpec(SecondaryAbilityClass, 1, -1, this));
		TertiaryAbilitySpecHandle = Component->GiveAbility(FGameplayAbilitySpec(TertiaryAbilityClass, 1, -1, this));
		QuaternaryAbilitySpecHandle = Component->GiveAbility(FGameplayAbilitySpec(QuaternaryAbilityClass, 1, -1, this));
	}
}

void APlayerWeapon::OnUnselected(TEnumAsByte<UnselectReason> UnSelectReason)
{
	Super::OnUnselected(UnSelectReason);
	if (Component)
	{
		Component->SetRemoveAbilityOnEnd(PrimaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(SecondaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(TertiaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(QuaternaryAbilitySpecHandle);
	}
}

