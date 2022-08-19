// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Weapons/PlayerWeapons/PlayerWeapon.h"

#include "CDC/Components/CCombatComponent.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "CDC/Controllers/CPlayerController.h"



void APlayerWeapon::Init(UCCombatComponent* CombatComponent)
{
	Super::Init(CombatComponent);

	PC = Cast<ACPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void APlayerWeapon::OnSelected()
{
	Super::OnSelected();

	if (PC)
		PC->BindWeapon(this);
	
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

	if (PC)
		PC->UnbindWeapon(this);

	if (Component)
	{
		Component->SetRemoveAbilityOnEnd(PrimaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(SecondaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(TertiaryAbilitySpecHandle);
		Component->SetRemoveAbilityOnEnd(QuaternaryAbilitySpecHandle);
	}
}