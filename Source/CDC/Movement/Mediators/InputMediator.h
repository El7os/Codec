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
	DECLARE_MULTICAST_DELEGATE(InputMediatorBroadcast);

	/*
		Belki sadece update edilen gameplay tag yay�n s�ras�nda g�nderilebilir ve bu sayede kullan�c�lar�n b�t�n tagler aras�nda d�ng�ye girmesine gerek kalmaz.
	*/
public:

	UInputMediator();

	UFUNCTION(BlueprintCallable)
	void AddTag(const FGameplayTag& TagToAdd) { InputTags.AddTag(TagToAdd); MediatorUpdateBroadcast.Broadcast(); }

	UFUNCTION(BlueprintCallable)
	void RemoveTag(const FGameplayTag& TagToRemove) { InputTags.RemoveTag(TagToRemove); MediatorUpdateBroadcast.Broadcast(); }

	//UFUNCTION(BlueprintCallable)
	FORCEINLINE const FGameplayTagContainer& GetTags() { return InputTags; }
	
	InputMediatorBroadcast MediatorUpdateBroadcast;

private:

	UPROPERTY()
	FGameplayTagContainer InputTags;

	

	
};
