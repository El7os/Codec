// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DamageTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType, Blueprintable)
enum EDamageType
{
	EDamageType_Null UMETA(DisplayName = "Null"),
	EDamageType_Physical UMETA(DisplayName = "Physical"),
	EDamageType_Magical  UMETA(DisplayName = "Magical"),
	EDamageType_Electrical  UMETA(DisplayName = "Electrical"),
	EDamageType_Chemical  UMETA(DisplayName = "Chemical"),
	EDamageType_True  UMETA(DisplayName = "True")
};

USTRUCT(Blueprintable, BlueprintType)
struct FDamageSpec
{
	GENERATED_BODY()

public:


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float DamageMagnitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<EDamageType> DamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FGameplayTagContainer DamageTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		FGameplayTagContainer DamageProperties;


};

class CDC_API DamageTypes
{
public:
	DamageTypes();
	~DamageTypes();
};
