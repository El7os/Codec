// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

UCDefaultMovementStrategy::UCDefaultMovementStrategy()
	: UCMovementStrategy()
{
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
	UE_LOG(LogTemp, Warning, TEXT("Controller can't be reached"));
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
		float CurrentSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
		float NewSpeed = CurrentSpeed * (100 + RunnignSpeedPercent) / 100;
		SpeedContribution = NewSpeed - CurrentSpeed;
		Owner->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	}
}

void UCDefaultMovementStrategy::RunReleased()
{
	if (Owner && Owner->GetCharacterMovement())
	{
		Owner->GetCharacterMovement()->MaxWalkSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed - SpeedContribution;
	}

}

void UCDefaultMovementStrategy::Evade()
{
	UE_LOG(LogTemp, Display, TEXT("Evade input has been handled."))
}
