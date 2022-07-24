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

	void Forward(float AxisValue) override;

	void Right(float AxisValue) override;

	void RunPressed() override;

	void RunReleased() override;

	void Evade() override;


private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RunningInterpSpeed = 10.0f;

	float RunnignSpeedPercent = 15;

	bool bTargetSpeedEvaluated = false;
	float SpeedContribution;
};
