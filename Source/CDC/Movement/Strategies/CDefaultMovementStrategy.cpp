// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UCDefaultMovementStrategy::UCDefaultMovementStrategy()
	: UCMovementStrategy()
{
}

void UCDefaultMovementStrategy::PostInitProperties()
{
	Super::PostInitProperties();

	if (bAutoAdjustSpeed && Owner && Owner->GetCharacterMovement())
		Owner->GetCharacterMovement()->MaxWalkSpeed = CharacterSpeed;
}

void UCDefaultMovementStrategy::Forward(float AxisValue)
{
	if (!AxisValue) return;

	if (Owner && Owner->Controller)
	{
		const FVector Direction = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		Owner->AddMovementInput(Direction, AxisValue);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Controller can't be reached"));
}

void UCDefaultMovementStrategy::Right(float AxisValue)
{
	if (!AxisValue) return;

	if (Owner && Owner->Controller)
	{
		const FVector Direction = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		Owner->AddMovementInput(Direction, AxisValue);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Controller can't be reached"));
	
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

		default:
			break;
		}
	}
}

void UCDefaultMovementStrategy::RunReleased()
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
	}

}

void UCDefaultMovementStrategy::Evade()
{
	UE_LOG(LogTemp, Display, TEXT("Evade input has been handled."))
}
