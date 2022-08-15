// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "InputMediator.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UInputMediator : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_OneParam(InputMediatorBroadcast, const UInputMediator* const);

	/*
		Belki sadece update edilen gameplay tag yayýn sýrasýnda gönderilebilir ve bu sayede kullanýcýlarýn bütün tagler arasýnda döngüye girmesine gerek kalmaz.
	*/
public:

	UInputMediator();

	UFUNCTION(BlueprintCallable)
	void AddTag(const FGameplayTag& TagToAdd) { InputTags.AddTag(TagToAdd); MediatorUpdateBroadcast.Broadcast(this); }

	UFUNCTION(BlueprintCallable)
	void RemoveTag(const FGameplayTag& TagToRemove) { InputTags.RemoveTag(TagToRemove); MediatorUpdateBroadcast.Broadcast(this); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsForwardInputBlocked() const { return InputTags.HasTag(ForwardInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsRightInputBlocked() const { return InputTags.HasTag(RightInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsMouseXInputBlocked() const { return InputTags.HasTag(MouseXInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsMouseYInputBlocked() const { return InputTags.HasTag(MouseYInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsAction1InputBlocked() const  { return InputTags.HasTag(Action1InputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsAction2InputBlocked() const { return InputTags.HasTag(Action2InputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsWeaponPrimaryInputBlocked()  const { return InputTags.HasTag(WeaponPrimaryInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsWeaponSecondaryInputBlocked() const { return InputTags.HasTag(WeaponSecondaryInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsWeaponTertiaryInputBlocked() const { return InputTags.HasTag(WeaponTertiaryInputBlockerTag); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool bIsWeaponQuaternaryInputBlocked() const { return InputTags.HasTag(WeaponQuaternaryInputBlockerTag); } 

	InputMediatorBroadcast MediatorUpdateBroadcast;
private:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag ForwardInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag RightInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag MouseXInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag MouseYInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag Action1InputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag Action2InputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag WeaponPrimaryInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag WeaponSecondaryInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag WeaponTertiaryInputBlockerTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Block", meta = (AllowPrivateAccess = "true"))
	FGameplayTag WeaponQuaternaryInputBlockerTag;

	UPROPERTY()
	FGameplayTagContainer InputTags;
	
};
