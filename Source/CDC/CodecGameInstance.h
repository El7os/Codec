// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodecGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UCodecGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Weapons|PlayerWeapons")
	TArray<TSubclassOf<class AWeapon>> PlayerWeaponClasses;

	/*
	* Spawns corresponding weapon to id  at specified transform in specified world.
	* Returns the weapon type as it is requested.
	* If only a AWeapon is needed use CreateWeapon insted of.
	*/
	template<typename T>
	T* SpawnWeapon(UWorld* const OutWorldContext, int WeaponID, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)))
	{
		if (OutWorldContext && PlayerWeaponClasses.Num() > WeaponID && WeaponID >= 0)
		{
			return OutWorldContext->SpawnActor<T>(PlayerWeaponClasses[WeaponID], CustomTransformToSpawn);
		}
#ifdef WITH_EDITOR
		else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned (Weapon ID : %i)"), WeaponID);
#endif
		return nullptr;
	}

	/*
	* Spawns a weapon object of Class at specified transform in specified world.
	* Returns the weapon type as it is requested.
	* If only a weapon is needed use CreateWeapon insted of.
	*/
	template<typename T>
	T* SpawnWeapon(UWorld* const OutWorldContext, UClass* const Class, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)))
	{
		if (OutWorldContext && Class)
		{
			return OutWorldContext->SpawnActor<T>(Class, CustomTransformToSpawn);
		}
#ifdef WITH_EDITOR
		else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned"));
#endif
		return nullptr;
	}

	/*
	* Spawns corresponding weapon to id  at specified transform in specified world.
	* Returns a AWeapon
	*  If weapon object type of a particual class is needed, use SpawnWeapon.
	*/
	AWeapon* CreateWeapon(UWorld* const OutWorldContext, int WeaponID, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)));

	/*
	* Spawns a weapon object of Class at specified transform in specified world.
	* Returns a AWeapon
	* If weapon object type of a particual class is needed, use SpawnWeapon.
	*/
	AWeapon* CreateWeapon(UWorld* const OutWorldContext, UClass* const Class, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)));

	/*
	* For blueprint only.
	* USe CreateWeapon insted of.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (DisplayName = "Create Weapon By ID"))
	AWeapon* BP_CreateWeaponByID(UWorld* const OutWorldContext, int WeaponID, UPARAM(ref) FTransform& CustomTransformToSpawn);

	/*
	* For blueprint only.
	* USe CreateWeapon insted of.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (DisplayName = "Create Weapon By Class"))
	AWeapon* BP_CreateWeaponByClass(UWorld* const OutWorldContext, UClass* const Class, UPARAM(ref) FTransform& CustomTransformToSpawn);

private:

};
