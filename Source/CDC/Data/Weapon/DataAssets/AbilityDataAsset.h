// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"
#include "AbilityDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CDC_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	FORCEINLINE const FName& GetName() { return Name; }

	FORCEINLINE UClass* const GetClass() { return Class; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCGameplayAbility> Class;
};

UCLASS(Blueprintable, BlueprintType)
class CDC_API UPlayerAbilityDataAsset : public UAbilityDataAsset
{
	GENERATED_BODY()

public:
	
	FORCEINLINE const UTexture2D* const GetIcon() { return Icon; }

	FORCEINLINE const FText& GetDescription() { return Description; }

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FText Description;
};
