// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/AttributeSets/CombatAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CDC/Characters/CPlayerCharacter.h"

float UCombatAttributeSet::GetHealth() const
{
	return FMath::Max(Health.GetCurrentValue(), 0.0f);
}

void UCombatAttributeSet::SetHealth(float NewVal)
{
	NewVal = FMath::Max(NewVal, 0.0f);

	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (ensure(ASC))
	{
		ASC->SetNumericAttributeBase(GetHealthAttribute(), NewVal);
	}
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);


	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		SetMovementSpeed(Data.EvaluatedData.Magnitude);
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
		if (ensure(ASC) && ASC->GetOwner())
		{
			if (UCharacterMovementComponent* MovementComponent = ASC->GetOwner()->FindComponentByClass<UCharacterMovementComponent>())
			{
				MovementComponent->MaxWalkSpeed = GetMovementSpeed();
			}
		}
	}

}


