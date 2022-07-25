// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Movement/Strategies/CMovementStrategy.h"
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

	void RunPressed() override;

	void RunReleased() override;

	void Evade() override;


private:

	/*
		It represents the calculation type of the additional speed when the player character runs
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", Category = "Movement|Run", ExposeOnSpawn = "true"))
	TEnumAsByte<EAccelerationType> AccelerationType = EAccelerationType::Fixed;
	
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
};
