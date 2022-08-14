// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TestCharacterAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UTestCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FGameplayAttributeData MovementSpeed = 600.0f;

	ATTRIBUTE_ACCESSORS(UTestCharacterAttributeSet, MovementSpeed);

};
