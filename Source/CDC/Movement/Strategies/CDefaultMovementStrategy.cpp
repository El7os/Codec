// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CDC/GameplayAbilities/CGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "CDC/AttributeSets/CombatAttributeSet.h"

UCDefaultMovementStrategy::UCDefaultMovementStrategy() : UCMovementStrategy()
{
}

void UCDefaultMovementStrategy::PostInitProperties()
{
	Super::PostInitProperties();

	if (Owner)
	{
		OwnerCombatComponent = Owner->GetAbilitySystemComponent();
		if (OwnerCombatComponent)
		{
			EvadeSpecHandle = OwnerCombatComponent->GiveAbility(FGameplayAbilitySpec(EvadeAbilityClass, 1, -1, this));

			SlideSpecHandle = OwnerCombatComponent->GiveAbility(FGameplayAbilitySpec(SlideAbilityClass, 1, -1, this));
		}
#ifdef WITH_EDITOR
		else
			UE_LOG(LogTemp,Warning,TEXT("Owner's ability system component could not be reached Source:(%s), Owner(%s)"),*GetName(), *Owner->GetName())
#endif	
		SetCharacterMovementProperties();
	}
}

void UCDefaultMovementStrategy::SetCharacterMovementProperties()
{
	if (UCharacterMovementComponent* MovementComp = Owner->GetCharacterMovement())
	{
		MovementComp->bOrientRotationToMovement = true;
		MovementComp->MaxAcceleration = 1000.0f;

		if (bAutoAdjustSpeed && OwnerCombatComponent)
		{
			if (OwnerCombatComponent)
			{
				FGameplayEffectContextHandle EffectContextHandle = OwnerCombatComponent->MakeEffectContext();
				EffectContextHandle.AddInstigator(Owner, Owner);
				EffectContextHandle.AddSourceObject(this);

				FGameplayEffectSpecHandle EffectSpecHandle = OwnerCombatComponent->MakeOutgoingSpec(RunningGameplayEffectClass, 1, EffectContextHandle);

				if (EffectContextHandle.IsValid())
				{
					EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.DataTag.Running.Speed")), CharacterSpeed);
					ActiveRunningEffectHandle = OwnerCombatComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
				}
			}
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
	UE_LOG(LogTemp, Warning, TEXT("Movement Speed : %f"), Owner->GetCharacterMovement()->MaxWalkSpeed);
	switch (AccelerationType)
	{
	case EAccelerationType::ByPrecent:
		SpeedContribution = Owner->GetCharacterMovement()->MaxWalkSpeed * (AdditionalPercent / 100);
		break;
	case EAccelerationType::Fixed:
		SpeedContribution = AdditionalSpeed;
		break;
	}

	if (OwnerCombatComponent)
	{
		FGameplayEffectContextHandle EffectContextHandle = OwnerCombatComponent->MakeEffectContext();
		EffectContextHandle.AddInstigator(Owner,Owner);
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle EffectSpecHandle = OwnerCombatComponent->MakeOutgoingSpec(RunningGameplayEffectClass, 1, EffectContextHandle);

		if (EffectContextHandle.IsValid())
		{
			EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.DataTag.Running.Speed")), SpeedContribution + Owner->GetCharacterMovement()->MaxWalkSpeed);
			ActiveRunningEffectHandle = OwnerCombatComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		}
		bIsRunning = true;
	}	
	UE_LOG(LogTemp, Warning, TEXT("Movement Speed : %f"), Owner->GetCharacterMovement()->MaxWalkSpeed);
}

void UCDefaultMovementStrategy::Action1Released()
{
	
	if (OwnerCombatComponent)
	{
		OwnerCombatComponent->RemoveActiveGameplayEffect(ActiveRunningEffectHandle);
		ActiveRunningEffectHandle.Invalidate();
		
		FGameplayEffectContextHandle EffectContextHandle = OwnerCombatComponent->MakeEffectContext();
		EffectContextHandle.AddInstigator(Owner, Owner);
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle EffectSpecHandle = OwnerCombatComponent->MakeOutgoingSpec(RunningGameplayEffectClass, 1, EffectContextHandle);

		if (EffectContextHandle.IsValid())
		{
			EffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(TEXT("GameplayEffect.DataTag.Running.Speed")), Owner->GetCharacterMovement()->MaxWalkSpeed - SpeedContribution);
			ActiveRunningEffectHandle = OwnerCombatComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
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
