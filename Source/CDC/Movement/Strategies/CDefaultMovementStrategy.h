// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Movement/Strategies/CMovementStrategy.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "CDefaultMovementStrategy.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UCDefaultMovementStrategy : public UCMovementStrategy
{
	GENERATED_BODY()

public:

	UCDefaultMovementStrategy();

	void PostInitProperties() override;

	void Forward(float AxisValue) override;

	void Right(float AxisValue) override;

	void Action1Pressed() override;

	void Action1Released() override;

	void Action2Pressed() override;

	void ForceAction1ToStop() override;

private:

	UFUNCTION()
	void SetCharacterMovementProperties();

	UPROPERTY()
	class UAbilitySystemComponent* OwnerCombatComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Run", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> RunningGameplayEffectClass;
	
	/*
	* A gameplay ability class makes the player evade. 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Category = "Movement|Evade"))
	TSubclassOf<class UCGameplayAbility> EvadeAbilityClass;

	/*
	* A gameplay ability class that makes the player slide on the ground.
	* In order for player to slide on groud, the player must evade while running.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", Category = "Movement|Slide"))
	TSubclassOf<class UCGameplayAbility> SlideAbilityClass;

	/*
		It represents the calculation type of the additional speed when the player character runs
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "Movement|Run", ExposeOnSpawn = "true"))
	TEnumAsByte<EAccelerationType> AccelerationType = EAccelerationType::Fixed;

	UPROPERTY()
	FActiveGameplayEffectHandle ActiveRunningEffectHandle;

	UPROPERTY()
	FGameplayAbilitySpecHandle EvadeSpecHandle;
	
	UPROPERTY()
	FGameplayAbilitySpecHandle SlideSpecHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", InlineEditConditionToggle, Category = "Movement|Walk",ExposeOnSpawn = "true"))
	bool bAutoAdjustSpeed = true;

	/*
		It changes the players speed to this speed if it is true, otherwise it doesn't do anything.	
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = "0",Category = "Movement|Walk", EditCondition = "bAutoAdjustSpeed", ExposeOnSpawn = "true",  Units = "Cm/s"))
	float CharacterSpeed = 600.0f;

	/*
		The additional speed amount that added to the characters speed when the character runs.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "Movement|Run", ExposeOnSpawn = "true", EditCondition = "AccelerationType==EAccelerationType::Fixed",Units = "Cm/s"))
	float AdditionalSpeed = 500.0f;
	
	/*
		The additional speed percent relative to the players current speed. It is added to players speed.
		(For exp for a character with speed 100, 15 means new speed will be 115)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "Movement|Run", ExposeOnSpawn = "true", EditCondition = "AccelerationType==EAccelerationType::ByPrecent"))
	float AdditionalPercent = 20.0f;


	/*
		The added speed amount when the player runs. It only valids if the player is accelerating by percent. 
	*/
	UPROPERTY()
	float SpeedContribution = 0.0f;

	UPROPERTY()
	bool bIsRunning = false;


	
};
