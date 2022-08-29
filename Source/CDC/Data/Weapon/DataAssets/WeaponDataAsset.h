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

	FORCEINLINE const FName& GetName() const { return Name; }

	FORCEINLINE UClass* const GetClass() const { return Class; }

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

	FORCEINLINE const UTexture2D* const GetIcon() const { return Icon; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetPriamaryAbilityDataAsset() const { return PrimaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetSecondaryAbilityyDataAsset() const { return SecondaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetTertiaryAbilityyDataAsset() const { return TertiaryAbilityDataAsset; }

	FORCEINLINE const UPlayerAbilityDataAsset* const GetQuaternaryAbilityyDataAsset() const { return QuaternaryAbilityDataAsset; }

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

	FORCEINLINE const TArray<UAbilityDataAsset*>& GetAbilityClasses() const { return AbilityDataAssets; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UAbilityDataAsset*> AbilityDataAssets;
};