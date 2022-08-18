// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMovementStrategy.generated.h"

/**
 *
 */

 /*
	 Bu ve daha sonraki movement strategylerin kullanacaðý enum
	 sýnýflarý Movement adlý bir namespace içerisinde
	 daha düzenli olarak tutulabilir.
 */
UENUM()
enum EAccelerationType
{
	ByPrecent,
	Fixed
};


UCLASS(Blueprintable, Abstract)
class CDC_API UCMovementStrategy : public UObject
{
	GENERATED_BODY()

public:

	UCMovementStrategy();

	virtual void Forward(float AxisValue) {};

	virtual void Right(float AxisValue) {};

	virtual void MouseX(float AxisValue) {};

	virtual void MouseY(float AxisValue) {};

	virtual void Action1Pressed() {};

	virtual void Action1Released() {};

	virtual void ForceAction1ToStop() {};

	virtual void Action2Pressed() {};

	virtual void Action2Released() {};

	virtual void ForceAction2ToStop() {};

protected:

	UPROPERTY()
		class ACPlayerCharacter* Owner = nullptr;

};