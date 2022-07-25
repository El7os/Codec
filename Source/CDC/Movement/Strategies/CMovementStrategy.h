// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMovementStrategy.generated.h"

/**
 * 
 */

UENUM()
enum EAccelerationType
{
	ByPrecent,
	Fixed
};


UCLASS(Blueprintable)
class CDC_API UCMovementStrategy : public UObject
{
	GENERATED_BODY()
	
public:

	UCMovementStrategy();

	virtual void Forward(float AxisValue) {};
	
	virtual void Right(float AxisValue) {};

	virtual void MouseX(float AxisValue) {};

	virtual void MouseY(float AxisValue) {};

	virtual void RunPressed() {};

	virtual void RunReleased() {};

	virtual void Evade() {};


protected:

	class ACPlayerCharacter* Owner = nullptr;
};
