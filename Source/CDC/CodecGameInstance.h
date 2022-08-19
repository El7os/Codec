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
	/*
	* Spawns corresponding weapon to id  at specified transform in specified world.
	* Returns the weapon type as it is requested.
	* If only a AWeapon is needed use CreateWeapon insted of.
	*/
	template<typename T>
	T* SpawnWeapon(UWorld* const OutWorldContext, int32 WeaponID, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)))
	{
		if (GetWorld())
		{
			if (UWeaponDataAsset** const WeaponDA = WeaponSet.Find(WeaponID))
			{
				if (UClass* const Class = (*WeaponDA)->GetClass())
				{
					return GetWorld()->SpawnActor<T>(Class, CustomTransformToSpawn);
				}
			}
		}
#ifdef WITH_EDITOR
		else UE_LOG(LogTemp, Warning, TEXT("Weapon cannot be spawned, a weapon that associated with the ID(%i) cannot be found or OutWorldContext isn't valid."), WeaponID);
#endif

		return nullptr;
	}

	/*
	* Spawns a weapon object of Class at specified transform in specified world.
	* Returns the weapon type as it is requested.
	* If only a weapon is needed use CreateWeapon insted of.
	*/
	template<typename T>
	T* SpawnWeapon(UClass* const Class, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)))
	{
		if (GetWorld() && Class)
			return GetWorld()->SpawnActor<T>(Class, CustomTransformToSpawn);
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
	AWeapon* CreateWeapon(int32 WeaponID, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)));

	/*
	* Spawns a weapon object of Class at specified transform in specified world.
	* Returns a AWeapon
	* If weapon object type of a particual class is needed, use SpawnWeapon.
	*/
	AWeapon* CreateWeapon(UClass* const Class, const FTransform& CustomTransformToSpawn = FTransform(FVector(0.0f, 0.0f, -1000.0f)));

	/*
	* For blueprint only.
	* Use CreateWeapon insted of.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (DisplayName = "Create Weapon By ID"))
	AWeapon* BP_CreateWeaponByID(int32 WeaponID, UPARAM(ref) FTransform& CustomTransformToSpawn);

	/*
	* For blueprint only.
	* Ue CreateWeapon insted of.
	*/
	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (DisplayName = "Create Weapon By Class"))
	AWeapon* BP_CreateWeaponByClass(UClass* const Class, UPARAM(ref) FTransform& CustomTransformToSpawn);

	UFUNCTION(BlueprintCallable, Category = "Weapon", meta =(DisplayName = "Get Weapon Data By ID"))
	FORCEINLINE const class UWeaponDataAsset* const GetWeaponDataByID(int WeaponID);

	UFUNCTION(BlueprintCallable, Category = "Weapon", meta = (DisplayName = "Get Weapon Data By Class"))
	const class UWeaponDataAsset* const GetWeaponDataByClass(UClass* const Class);

	template<typename T>
	FORCEINLINE const T* const GetWeaponData(int WeaponID)
	{
		return Cast<T>(*WeaponSet.Find(WeaponID));
	}

	template<typename T>
	const T* const GetWeaponData(UClass* const Class)
	{
		for (const TTuple<int, UWeaponDataAsset*>& i : WeaponSet)
		{
			if (i.Value && i.Value->GetClass == Class)
				return Cast<T>(i.Value);
		}
		return nullptr;
	}

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat|Weapons", meta = (AllowPrivateAccess = "true"))
	TMap<int, class UWeaponDataAsset*> WeaponSet;

};
