// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Weapons/Weapon.h"
#include "CDC/Movement/Mediators/InputMediator.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "PlayerWeapon.generated.h"

#define DECLARE_INPUT_FUNCTIONS(InputName)\
virtual void InputName##Pressed() {if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}\
virtual void InputName##DelayedPressed() {if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}\
virtual void InputName##BeginHover(){if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}\
virtual void InputName##OnHover(float ElapsedTime){if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}\
virtual void InputName##EndHover(float TotalTime){if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}\
virtual void InputName##Released(){if(InputMediator && InputMediator->GetTags().HasTag(InputName##AbilityInputBlockerTag)) return;}

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
	friend class ACPlayerController;
public:

	APlayerWeapon();

protected:

	DECLARE_INPUT_FUNCTIONS(Primary)
	DECLARE_INPUT_FUNCTIONS(Secondary)
	DECLARE_INPUT_FUNCTIONS(Tertiary)
	DECLARE_INPUT_FUNCTIONS(Quaternary)

	virtual void OnSelected() override;

	virtual void OnUnselected(TEnumAsByte<UnselectReason> UnSelectReason) override;

	class UInputMediator* InputMediator = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag PrimaryAbilityInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag SecondaryAbilityInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag TertiaryAbilityInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag QuaternaryAbilityInputBlockerTag;

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


};
