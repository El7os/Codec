// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"
#include "AbilitySystemComponent.h"


UCDefaultMovementStrategy::UCDefaultMovementStrategy() : UCMovementStrategy()
{
}

void UCDefaultMovementStrategy::PostInitProperties()
{
	Super::PostInitProperties();

	if (Owner)
	{
		SetCharacterMovementProperties();
		OwnerCombatComponent = Owner->GetAbilitySystemComponent();
		if (OwnerCombatComponent)
		{
			EvadeSpecHandle = OwnerCombatComponent->GiveAbility(FGameplayAbilitySpec(EvadeAbilityClass, 1, -1, this));

			SlideSpecHandle = OwnerCombatComponent->GiveAbility(FGameplayAbilitySpec(SlideAbilityClass, 1, -1, this));
		}
#if WITH_EDITOR
		else
			UE_LOG(LogTemp,Warning,TEXT("Owner's ability system component could not be reached Source:(%s), Owner(%s)"),*GetName(), *Owner->GetName())
#endif
			
	}
}

void UCDefaultMovementStrategy::SetCharacterMovementProperties()
{
	UCharacterMovementComponent* MovementComp = Owner->GetCharacterMovement();
	if (MovementComp)
	{
		MovementComp->bOrientRotationToMovement = true;
		MovementComp->MaxAcceleration = 1000.0f;

		if (bAutoAdjustSpeed)
		{
			MovementComp->MaxWalkSpeed = CharacterSpeed;
		}

	}

	Owner->GetSpringArm()->bUsePawnControlRotation = false;
	Owner->GetSpringArm()->bInheritPitch = false;
	Owner->GetSpringArm()->bInheritRoll = false;
	Owner->GetSpringArm()->bInheritYaw = false;
}

void UCDefaultMovementStrategy::Forward(float AxisValue)
{
	if (!AxisValue) return;

	if (Owner)
	{
		Owner->AddMovementInput(FVector(1.f, 0.f, 0.f), AxisValue);
	}
}

void UCDefaultMovementStrategy::Right(float AxisValue)
{
	if (!AxisValue) return;

	if (Owner)
	{
		Owner->AddMovementInput(FVector(0.f, 1.f, 0.f), AxisValue);
	}
	
}

void UCDefaultMovementStrategy::Action1Pressed()
{
	/*if (OwnerCombatComponent)
	{
		FGameplayEffectContextHandle EffectContext = OwnerCombatComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpec = OwnerCombatComponent->MakeOutgoingSpec(RunningEffect, 1, EffectContext);
		ActiveHandle = OwnerCombatComponent->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	}
	return;*/
	if (Owner && Owner->GetCharacterMovement())
	{
		switch (AccelerationType)
		{
		case EAccelerationType::ByPrecent:

			 SpeedContribution = Owner->GetCharacterMovement()->MaxWalkSpeed * (AdditionalPercent / 100);
			 Owner->GetCharacterMovement()->MaxWalkSpeed += SpeedContribution;

			break;
		case EAccelerationType::Fixed:

			Owner->GetCharacterMovement()->MaxWalkSpeed += AdditionalSpeed;
			
			break;
		}
		bIsRunning = true;
	}
}

void UCDefaultMovementStrategy::Action1Released()
{
	if (Owner && Owner->GetCharacterMovement())
	{
		switch (AccelerationType)
		{
		case EAccelerationType::ByPrecent:

			Owner->GetCharacterMovement()->MaxWalkSpeed -= SpeedContribution;
			SpeedContribution = 0;

			break;
		case EAccelerationType::Fixed:

			Owner->GetCharacterMovement()->MaxWalkSpeed -= AdditionalSpeed;

			break;

		default:
			break;
		}
		bIsRunning = false;
	}
}

void UCDefaultMovementStrategy::Action2Pressed()
{
	if (OwnerCombatComponent)
		bIsRunning ? OwnerCombatComponent->TryActivateAbility(SlideSpecHandle) : OwnerCombatComponent->TryActivateAbility(EvadeSpecHandle);
}

void UCDefaultMovementStrategy::ForceAction1ToStop()
{
	Super::ForceAction1ToStop();

	Action1Released();
}
