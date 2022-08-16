// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Controllers/CPlayerController.h"

#include "CDC/Movement/Mediators/InputMediator.h"
#include "CDC/Weapons/PlayerWeapons/PlayerWeapon.h"


ACPlayerController::ACPlayerController() : APlayerController()
{
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAxis(TEXT("Weapon_Primary_Ability_Input"), this, &ACPlayerController::PrimaryAxisFunc);
		InputComponent->BindAction(TEXT("Weapon_Primary_Ability_Input"), IE_Pressed, this, &ACPlayerController::PrimaryActionPressedFunc);
		InputComponent->BindAction(TEXT("Weapon_Primary_Ability_Input"), IE_Released, this, &ACPlayerController::PrimaryActionReleasedFunc);

		InputComponent->BindAxis(TEXT("Weapon_Secondary_Ability_Input"), this, &ACPlayerController::SecondaryAxisFunc);
		InputComponent->BindAction(TEXT("Weapon_Secondary_Ability_Input"), IE_Pressed, this, &ACPlayerController::SecondaryActionPressedFunc);
		InputComponent->BindAction(TEXT("Weapon_Secondary_Ability_Input"), IE_Released, this, &ACPlayerController::SecondaryActionReleasedFunc);

		InputComponent->BindAxis(TEXT("Weapon_Tertiary_Ability_Input"), this, &ACPlayerController::TertiaryAxisFunc);
		InputComponent->BindAction(TEXT("Weapon_Tertiary_Ability_Input"), IE_Pressed, this, &ACPlayerController::TertiaryActionPressedFunc);
		InputComponent->BindAction(TEXT("Weapon_Tertiary_Ability_Input"), IE_Released, this, &ACPlayerController::TertiaryActionReleasedFunc);

		InputComponent->BindAxis(TEXT("Weapon_Quaternary_Ability_Input"), this, &ACPlayerController::QuaternaryAxisFunc);
		InputComponent->BindAction(TEXT("Weapon_Quaternary_Ability_Input"), IE_Pressed, this, &ACPlayerController::QuaternaryActionPressedFunc);
		InputComponent->BindAction(TEXT("Weapon_Quaternary_Ability_Input"), IE_Released, this, &ACPlayerController::QuaternaryActionReleasedFunc);
	}

	PrimaryInputExtractor.SetPlayerController(this);
	SecondaryInputExtractor.SetPlayerController(this);
	TertiaryInputExtractor.SetPlayerController(this);
	QuaternaryInputExtractor.SetPlayerController(this);

}

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UInputMediator* InputMediator = GetGameInstance()->GetSubsystem<UInputMediator>())
	{
		InputMediator->MediatorUpdateBroadcast.AddUObject(this, &ACPlayerController::OnInputMediatorUpdated);
	}
}

void ACPlayerController::OnInputMediatorUpdated(const UInputMediator* const InputMediator)
{
	if (UInputMediator* InputMediator = GetGameInstance()->GetSubsystem<UInputMediator>())
	{
		bool CacheForPrimary = InputMediator->bIsWeaponPrimaryInputBlocked();
		bool CacheForSecondary = InputMediator->bIsWeaponSecondaryInputBlocked();
		bool CacheForTertiary = InputMediator->bIsWeaponTertiaryInputBlocked();
		bool CacheForQuaternary = InputMediator->bIsWeaponQuaternaryInputBlocked();

		if (CacheForPrimary && !PrimaryInputExtractor.GetBlockExtraction())
			PrimaryAbilityBlockedDelegate.ExecuteIfBound();

		if (CacheForSecondary && !SecondaryInputExtractor.GetBlockExtraction())
			SecondaryAbilityBlockedDelegate.ExecuteIfBound();

		if (CacheForTertiary && !TertiaryInputExtractor.GetBlockExtraction())
			TertiaryAbilityBlockedDelegate.ExecuteIfBound();

		if (CacheForQuaternary && !QuaternaryInputExtractor.GetBlockExtraction())
			QuaternaryAbilityBlockedDelegate.ExecuteIfBound();

		PrimaryInputExtractor.SetBlockExtraction(CacheForPrimary);
		SecondaryInputExtractor.SetBlockExtraction(CacheForSecondary);
		TertiaryInputExtractor.SetBlockExtraction(CacheForTertiary);
		QuaternaryInputExtractor.SetBlockExtraction(CacheForQuaternary);

	}
	 
}

void ACPlayerController::BindWeapon(APlayerWeapon* const Weapon)
{
	if (Weapon)
	{
		PrimaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryPressed);
		PrimaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryDelayedPressed);
		PrimaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryBeginHover);
		PrimaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryOnHover);
		PrimaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryEndHover);
		PrimaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::PrimaryReleased);
		PrimaryAbilityBlockedDelegate.BindUObject(Weapon, &APlayerWeapon::OnPrimaryInputBlocked);

		SecondaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryPressed);
		SecondaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryDelayedPressed);
		SecondaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryBeginHover);
		SecondaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryOnHover);
		SecondaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryEndHover);
		SecondaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryReleased);
		SecondaryAbilityBlockedDelegate.BindUObject(Weapon, &APlayerWeapon::OnSecondaryInputBlocked);

		TertiaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryPressed);
		TertiaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryDelayedPressed);
		TertiaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryBeginHover);
		TertiaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryOnHover);
		TertiaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryEndHover);
		TertiaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryReleased);
		TertiaryAbilityBlockedDelegate.BindUObject(Weapon, &APlayerWeapon::OnTertiaryInputBlocked);

		QuaternaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryPressed);
		QuaternaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryDelayedPressed);
		QuaternaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryBeginHover);
		QuaternaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryOnHover);
		QuaternaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryEndHover);
		QuaternaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryReleased);
		QuaternaryAbilityBlockedDelegate.BindUObject(Weapon, &APlayerWeapon::OnQuaternaryInputBlocked);
	}
#ifdef WITH_EDITOR
	else
		UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be bounded, it is null %s"), __FUNCTION__);
#endif
}

void ACPlayerController::UnbindWeapon(APlayerWeapon* const Weapon)
{
	if (Weapon)
	{
		PrimaryInputExtractor.PressedDelegate.Unbind();
		PrimaryInputExtractor.DelayedPressedDelegate.Unbind();
		PrimaryInputExtractor.BeginHoverDelegate.Unbind();
		PrimaryInputExtractor.OnHoverDelegate.Unbind();
		PrimaryInputExtractor.EndHoverDelegate.Unbind();
		PrimaryInputExtractor.ReleasedDelegate.Unbind();
		PrimaryAbilityBlockedDelegate.Unbind();

		SecondaryInputExtractor.PressedDelegate.Unbind();
		SecondaryInputExtractor.DelayedPressedDelegate.Unbind();
		SecondaryInputExtractor.BeginHoverDelegate.Unbind();
		SecondaryInputExtractor.OnHoverDelegate.Unbind();
		SecondaryInputExtractor.EndHoverDelegate.Unbind();
		SecondaryInputExtractor.ReleasedDelegate.Unbind();
		SecondaryAbilityBlockedDelegate.Unbind();


		TertiaryInputExtractor.PressedDelegate.Unbind();
		TertiaryInputExtractor.DelayedPressedDelegate.Unbind();
		TertiaryInputExtractor.BeginHoverDelegate.Unbind();
		TertiaryInputExtractor.OnHoverDelegate.Unbind();
		TertiaryInputExtractor.EndHoverDelegate.Unbind();
		TertiaryInputExtractor.ReleasedDelegate.Unbind();
		TertiaryAbilityBlockedDelegate.Unbind();


		QuaternaryInputExtractor.PressedDelegate.Unbind();
		QuaternaryInputExtractor.DelayedPressedDelegate.Unbind();
		QuaternaryInputExtractor.BeginHoverDelegate.Unbind();
		QuaternaryInputExtractor.OnHoverDelegate.Unbind();
		QuaternaryInputExtractor.EndHoverDelegate.Unbind();
		QuaternaryInputExtractor.ReleasedDelegate.Unbind();
		QuaternaryAbilityBlockedDelegate.Unbind();
	}
#ifdef WITH_EDITOR
	else
	UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be unbounded, it is null %s"), __FUNCTION__);
#endif
}

