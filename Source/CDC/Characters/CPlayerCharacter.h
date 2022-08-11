// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Characters/CCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CPlayerCharacter.generated.h"
/**
 * 
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

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UInputMediator* const GetInputMediator() { return InputMediator; }


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

	UPROPERTY()
	class UInputMediator* InputMediator = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta = (AllowPrivateAccess = "true"))
	FGameplayTag ForwardAxisBlockerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta = (AllowPrivateAccess = "true"))
	FGameplayTag RightAxisBlockerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta = (AllowPrivateAccess = "true"))
	FGameplayTag Action1BlockerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input",meta = (AllowPrivateAccess = "true"))
	FGameplayTag Action2BlockerTag;
	
	//Test

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ForwardInputAction = nullptr;*/

};


