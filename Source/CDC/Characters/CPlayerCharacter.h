// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Characters/CCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CPlayerCharacter.generated.h"
/**
 * The base class of all characters that can be used by the player.
 * It responsible for having the ability system component and delegating 
 * the input to strategies.The Input Mediator blocks the input flow at this level.
 */
UCLASS()
class CDC_API ACPlayerCharacter : public ACCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	ACPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void ChangeMovementStrategy(class UCMovementStrategy* const NewStrategy);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USpringArmComponent* const GetSpringArm() { return SpringArm;}


protected:

	void BeginPlay() override;

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
	void Action1Pressed();

	UFUNCTION()
	void Action1Released();

	UFUNCTION()
	void Action2Pressed();

	UFUNCTION()
	void Action2Released();

	UFUNCTION()
	void OnInputMediatorUpdated(const class UInputMediator* const InputMediator);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCMovementStrategy> InitialMovementStrategyClass;

	UPROPERTY()
	class UCMovementStrategy* MovementStrategy = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCCombatComponent* CombatComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastForwardInputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastRightInputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastAction1InputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastAction2InputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastMouseXInputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool LastMouseYInputQueryResult = true;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool bIsAction1Active = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Input")
	bool bIsAction2Active = false;


};


