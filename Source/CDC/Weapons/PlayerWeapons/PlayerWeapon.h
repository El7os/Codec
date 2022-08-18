// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Weapons/Weapon.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PlayerWeapon.generated.h"

#define DEFINE_INPUT_FUNCTIONS(InputName)\
virtual void InputName##Pressed() {}\
virtual void InputName##DelayedPressed() {}\
virtual void InputName##BeginHover(){}\
virtual void InputName##OnHover(float ElapsedTime){}\
virtual void InputName##EndHover(float TotalTime){}\
virtual void InputName##Released(){}\
virtual void On##InputName##InputBlocked() {};


#define OVERRIDE_DECLERATION_OF_INPUT_FUNCTIONS(InputName)\
virtual void InputName##Pressed() override;\
virtual void InputName##DelayedPressed() override;\
virtual void InputName##BeginHover() override;\
virtual void InputName##OnHover(float ElapsedTime) override;\
virtual void InputName##EndHover(float TotalTime) override;\
virtual void InputName##Released() override;\
virtual void On##InputName##InputBlocked() override;


/**
 *
 */
UCLASS(Abstract)
class CDC_API APlayerWeapon : public AWeapon
{
	GENERATED_BODY()
		friend class ACPlayerController;

public:

	APlayerWeapon();

protected:

	DEFINE_INPUT_FUNCTIONS(Primary)
	DEFINE_INPUT_FUNCTIONS(Secondary)
	DEFINE_INPUT_FUNCTIONS(Tertiary)
	DEFINE_INPUT_FUNCTIONS(Quaternary)

	virtual void Init(class UCCombatComponent* CombatComponenent) override;

	virtual void OnSelected() override;

	virtual void OnUnselected(TEnumAsByte<UnselectReason> UnSelectReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCGameplayAbility> PrimaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCGameplayAbility> SecondaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCGameplayAbility> TertiaryAbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCGameplayAbility> QuaternaryAbilityClass;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGameplayAbilitySpecHandle PrimaryAbilitySpecHandle;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGameplayAbilitySpecHandle SecondaryAbilitySpecHandle;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGameplayAbilitySpecHandle TertiaryAbilitySpecHandle;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGameplayAbilitySpecHandle QuaternaryAbilitySpecHandle;

	UPROPERTY()
		class ACPlayerController* PC = nullptr;
};