// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Weapons/Weapon.h"
#include "PlayerWeapon.generated.h"

#define DECLARE_INPUT_FUNCTIONS(InputName)\
virtual void InputName##Pressed() {}\
virtual void InputName##DelayedPressed() {}\
virtual void InputName##BeginHover(){}\
virtual void InputName##OnHover(float ElapsedTime){}\
virtual void InputName##EndHover(float TotalTime){}\
virtual void InputName##Released(){}

#define OVERRIDE_DECLERATION_OF_INPUT_FUNCTIONS(InputName)\
virtual void InputName##Pressed() override;\
virtual void InputName##DelayedPressed() override;\
virtual void InputName##BeginHover() override;\
virtual void InputName##OnHover(float ElapsedTime) override;\
virtual void InputName##EndHover(float TotalTime) override;\
virtual void InputName##Released() override;



/**
 * 
 */
UCLASS(Abstract)
class CDC_API APlayerWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:

protected:

	DECLARE_INPUT_FUNCTIONS(Primary)
	DECLARE_INPUT_FUNCTIONS(Secondary)
	DECLARE_INPUT_FUNCTIONS(Tertiary)
	DECLARE_INPUT_FUNCTIONS(Quaternary)

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCGameplayAbility> PrimaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCGameplayAbility> SecondaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCGameplayAbility> TertiaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCGameplayAbility> QuaternaryAbilityClass;

};
