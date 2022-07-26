// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CDC/GameplayAbilities/Locomotion/CEvadeAbility.h"
#include "CDC/GameplayAbilities/Locomotion/CSlideAbility.h"
#include "AbilitySystemComponent.h"


UCDefaultMovementStrategy::UCDefaultMovementStrategy()
	: UCMovementStrategy()
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

void UCDefaultMovementStrategy::RunPressed()
{
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

void UCDefaultMovementStrategy::RunReleased()
{
	UE_LOG(LogTemp, Warning, TEXT("Run released"));
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

void UCDefaultMovementStrategy::Evade()
{
	if (OwnerCombatComponent)
		bIsRunning ? OwnerCombatComponent->TryActivateAbility(SlideSpecHandle) : OwnerCombatComponent->TryActivateAbility(EvadeSpecHandle);
#if WITH_EDITOR
	else
		UE_LOG(LogTemp,Warning, TEXT("Evade cannot be executed, Owner's comba component is null Source(%s)"), *GetName())
#endif
}
