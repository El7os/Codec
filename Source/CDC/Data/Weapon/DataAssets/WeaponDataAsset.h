// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"
#include "CDC/Weapons/Weapon.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
class UPlayerAbilityDataAsset;
class UAbilityDataAsset;

UCLASS(Blueprintable, BlueprintType)
class CDC_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	FORCEINLINE const FName& GetName() { return Name; }

	FORCEINLINE UClass* const GetClass() { return Class; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> Class;
};

UCLASS(Blueprintable, BlueprintType)
class CDC_API UPlayerWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()

public:

	FORCEINLINE const UTexture2D* const GetIcon() { return Icon; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetPriamaryAbilityDataAsset() { return PrimaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetSecondaryAbilityyDataAsset() { return SecondaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetTertiaryAbilityyDataAsset() { return TertiaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetQuaternaryAbilityyDataAsset() { return QuaternaryAbilityDataAsset; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerAbilityDataAsset* PrimaryAbilityDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerAbilityDataAsset* SecondaryAbilityDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerAbilityDataAsset* TertiaryAbilityDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerAbilityDataAsset* QuaternaryAbilityDataAsset = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class CDC_API UAIWeaponDataAsset : public UWeaponDataAsset
{
	GENERATED_BODY()

public:

	FORCEINLINE const TArray<UAbilityDataAsset*>& GetAbilityClasses() { return AbilityDataAssets; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UAbilityDataAsset*> AbilityDataAssets;
};