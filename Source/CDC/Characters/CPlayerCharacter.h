// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CDC/Characters/CCharacter.h"
#include "AbilitySystemInterface.h"
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

	UFUNCTION()
	FORCEINLINE void SetBlockAllMovement(bool BlockMovement) {bBlockWalking = bBlockRunning = bBlockEvade = BlockMovement;}

	UFUNCTION()
	FORCEINLINE void SetBlockWalkingOnly(bool BlockWalking) {bBlockWalking = BlockWalking;}

	UFUNCTION()
	FORCEINLINE void SetBlockRunningOnly(bool BlockRunning) { bBlockRunning = BlockRunning; RunReleased(); }

	UFUNCTION()
	FORCEINLINE void SetBlockEvadeOnly(bool BlockEvade) {bBlockEvade = BlockEvade;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USpringArmComponent* const GetSpringArm() { return SpringArm;}

	UPROPERTY()
	bool bBlockWalking = false;

	UPROPERTY()
	bool bBlockRunning = false;

	UPROPERTY()
	bool bBlockEvade = false;

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
	void RunPressed();

	UFUNCTION()
	void RunReleased();

	UFUNCTION()
	void Evade();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCMovementStrategy> InitialMovementStrategyClass;

	UPROPERTY()
	class UCMovementStrategy* MovementStrategy = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UActionEventMediator* EventMediator = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCCombatComponent* CombatComponent = nullptr;

};
