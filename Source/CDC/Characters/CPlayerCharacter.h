// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Characters/CCharacter.h"
#include "CPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:

	ACPlayerCharacter();

	void ChangeMovementStrategy(class UCMovementStrategy* const NewStrategy);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UFUNCTION()
	void Forward(float AxisValue);

	UFUNCTION()
	void Right(float AxisValue);

	UFUNCTION()
	void MouseX(float AxisValue);

	UFUNCTION()
	void MouseY(float AxisValue);

	UFUNCTION()
	void RunPressed();

	UFUNCTION()
	void RunReleased();

	UFUNCTION()
	void Evade();

	UPROPERTY()
	class UCMovementStrategy* MovementStrategy = nullptr;

	/*
	UPROPERTY()
	class UActionEventMediator* EventMediator = nullptr;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

};
