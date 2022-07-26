// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionEventMediator.generated.h"

/**
 * 
 */

namespace ActionEventMediator
{
	UENUM(BlueprintType, Blueprintable)
	enum Notification
	{
		BlockAllInput = 0 UMETA(ToolTip="It blocks all input(Weapon,Player Movement) via the mediator. It blocks the weapon by the way that the weapon can override it."),
		BlockAllInputByForce UMETA(ToolTip="It block all input(Weapon,Player Movement) via the mediator. It block the weapon by the way that the weapon cannot override it.") ,
		BlockMovementOnly UMETA(ToolTip="It blocks only the Player's movement including running/evade/sliding."),
		BlockWeaponOnly   UMETA(ToopTip="It blocks weapon input in currentl weapon, weapon can override this."),
		BlockWalkingOnly,
		BlockRunningOnly,
		BlockEvadeOnly,
		BlockSlideOnly,
		BlockWeaponOnlyByForce UMETA(ToolTip="It blocks weapon input in combat component and this effect cannot be overrided in weapon. If you want it to be overrideable by weapon use 'BlockWeaponOnly"),
		UnBlockAllInput,
		UnBlockMovementOnly,
		UnBlockWeaponOnly,
		UnBlockWalkingOnly,
		UnBlockRunningOnly,
		UnBlockEvadeOnly,
		UnBlockSlideOnly,
	};
}



UCLASS()
class CDC_API UActionEventMediator : public UObject
{
	GENERATED_BODY()
	
public:

	UActionEventMediator();

	UFUNCTION(BlueprintCallable)
	void SetCharacter(class ACPlayerCharacter* const OutPlayerCharacter);

	UFUNCTION(BlueprintCallable)
	void SetComponent(class UCCombatComponent* const Component);

	//void SetWeapon(class ACPlayerWeapon* const PlayerWeapon);
	
	void Notify(UObject* const Sender, int num, ...);

private:

	UFUNCTION()
	FORCEINLINE void SetBlockMovement(bool Block);

	UFUNCTION()
	FORCEINLINE void SetBlockRunning(bool Block);

	UFUNCTION()
	FORCEINLINE void SetBlockEvade(bool Block);

	UFUNCTION()
	FORCEINLINE void SetBlockWalking(bool Block);

	UFUNCTION()
	FORCEINLINE void SetBlockSlide(bool Block);

	UFUNCTION()
	FORCEINLINE void SetBlockWeapon(bool Block, bool ByForce);

	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ACPlayerCharacter* PlayerCharacter;

	class UCCombatComponent* Component;

	//class ACPlayerWeapon* PlayerWeapon;


};
