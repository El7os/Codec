// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Mediators/InputMediator.h"


UInputMediator::UInputMediator() 
	: UGameInstanceSubsystem()
	, ForwardInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Forward")))
	, RightInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Right")))
	, MouseXInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.MouseX")))
	, MouseYInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.MouseY")))
	, Action1InputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Action1")))
	, Action2InputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Action2")))
	, WeaponPrimaryInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Weapon.PrimaryAbility")))
	, WeaponSecondaryInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Weapon.SecondaryAbility")))
	, WeaponTertiaryInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Weapon.TertiaryAbility")))
	, WeaponQuaternaryInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Weapon.QaternaryAbility")))
{

}
