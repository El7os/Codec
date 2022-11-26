// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayEffectFunctionlibrary.generated.h"

/**
 * 
 */

UCLASS()
class CDC_API UGameplayEffectFunctionlibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void ApplyDamage() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyStatisticalDebuff() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyMark() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyDamageOverTime() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyDamageModification() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyCrowdControl() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyIndefiniteBuff() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyConditionallyIndefiniteBuff() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyToggleBuff() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyHeal() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyShield() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyInvisibility() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyCamouflage() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyInvalnurability() {};

	UFUNCTION(BlueprintCallable)
	static void ApplyUntargetability() {};
};
