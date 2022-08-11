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
	
public:

	UInputMediator();

	//UFUNCTION(BlueprintCallable)
	FORCEINLINE const FGameplayTagContainer& GetTags() { return InputTags; };

	UFUNCTION(BlueprintCallable)
	void AddTag(const FGameplayTag& TagToAdd) { InputTags.AddTag(TagToAdd); }

	UFUNCTION(BlueprintCallable)
	void RemoveTag(const FGameplayTag& TagToRemove) { InputTags.RemoveTag(TagToRemove); }

private:

	UPROPERTY()
	FGameplayTagContainer InputTags;

	
};
