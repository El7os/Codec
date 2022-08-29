// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Weapons/PlayerWeapons/PlayerWeapon.h"
#include "IronClaw.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API AIronClaw : public APlayerWeapon
{
	GENERATED_BODY()
	
public:


private:

	OVERRIDE_DECLERATION_OF_INPUT_FUNCTIONS(Primary);
};
