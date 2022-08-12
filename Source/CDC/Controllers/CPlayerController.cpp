// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Controllers/CPlayerController.h"

#include "CDC/Weapons/PlayerWeapons/PlayerWeapon.h"


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


		SecondaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryPressed);
		SecondaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryDelayedPressed);
		SecondaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryBeginHover);
		SecondaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryOnHover);
		SecondaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryEndHover);
		SecondaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::SecondaryReleased);


		TertiaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryPressed);
		TertiaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryDelayedPressed);
		TertiaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryBeginHover);
		TertiaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryOnHover);
		TertiaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryEndHover);
		TertiaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::TertiaryReleased);


		QuaternaryInputExtractor.PressedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryPressed);
		QuaternaryInputExtractor.DelayedPressedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryDelayedPressed);
		QuaternaryInputExtractor.BeginHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryBeginHover);
		QuaternaryInputExtractor.OnHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryOnHover);
		QuaternaryInputExtractor.EndHoverDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryEndHover);
		QuaternaryInputExtractor.ReleasedDelegate.BindUObject(Weapon, &APlayerWeapon::QuaternaryReleased);
	}
#if WITH_EDITOR
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


		SecondaryInputExtractor.PressedDelegate.Unbind();
		SecondaryInputExtractor.DelayedPressedDelegate.Unbind();
		SecondaryInputExtractor.BeginHoverDelegate.Unbind();
		SecondaryInputExtractor.OnHoverDelegate.Unbind();
		SecondaryInputExtractor.EndHoverDelegate.Unbind();
		SecondaryInputExtractor.ReleasedDelegate.Unbind();


		TertiaryInputExtractor.PressedDelegate.Unbind();
		TertiaryInputExtractor.DelayedPressedDelegate.Unbind();
		TertiaryInputExtractor.BeginHoverDelegate.Unbind();
		TertiaryInputExtractor.OnHoverDelegate.Unbind();
		TertiaryInputExtractor.EndHoverDelegate.Unbind();
		TertiaryInputExtractor.ReleasedDelegate.Unbind();


		QuaternaryInputExtractor.PressedDelegate.Unbind();
		QuaternaryInputExtractor.DelayedPressedDelegate.Unbind();
		QuaternaryInputExtractor.BeginHoverDelegate.Unbind();
		QuaternaryInputExtractor.OnHoverDelegate.Unbind();
		QuaternaryInputExtractor.EndHoverDelegate.Unbind();
		QuaternaryInputExtractor.ReleasedDelegate.Unbind();
	}
#if WITH_EDITOR
	else
	UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be unbounded, it is null %s"), __FUNCTION__);
#endif
}

