// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType, Blueprintable)
enum UnselectReason
{
	UnSelectReason_Swap UMETA(DisplayName = "Spaw", ToolTip = "It represents that the weapon is unselected in order to select other weapon."),
	UnSelectReason_Replace UMETA(DisplayName = "Replace", ToolTip = "It represents that the weapon is unselected in order to be replaced by some other weapon.")
};


UCLASS(Abstract)
class CDC_API AWeapon : public AActor
{
	GENERATED_BODY()
	friend class UCCombatComponent;

public:	
	AWeapon();
	
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	virtual void Init(class UCCombatComponent* CombatComponenent) { Component = CombatComponenent; };

	virtual void OnSelected() {};

	virtual void OnUnselected(TEnumAsByte<UnselectReason> Reason) {};

	class UCCombatComponent* Component;
};
