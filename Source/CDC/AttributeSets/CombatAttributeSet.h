// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UCombatAttributeSet, Health);
	FORCEINLINE float GetHealth() const;
	FORCEINLINE void SetHealth(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);

	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MovementSpeed);

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


protected:




private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MovementSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health = 1000.0f;
	
};
