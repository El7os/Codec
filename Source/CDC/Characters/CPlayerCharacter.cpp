// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Characters/CPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"

ACPlayerCharacter::ACPlayerCharacter() : ACCharacter()
{
	//Create Actin Event Mediator object
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 110.0f;

	MovementStrategy = CreateDefaultSubobject<UCDefaultMovementStrategy>("Default Movement Strategy");
	if(MovementStrategy)
		UE_LOG(LogTemp, Warning, TEXT("Movement strategy is valid. C"))
	else
		UE_LOG(LogTemp, Warning, TEXT("Movement strategy isn't valid. C"));

}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//These mappings will be changed with PlayerEnchancedInput system.

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACPlayerCharacter::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACPlayerCharacter::Right);
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &ACPlayerCharacter::MouseX);
	PlayerInputComponent->BindAxis(TEXT("MouseY"), this, &ACPlayerCharacter::MouseY);

	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ACPlayerCharacter::RunPressed);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ACPlayerCharacter::RunReleased);
	PlayerInputComponent->BindAction(TEXT("Evade"), IE_Pressed, this, &ACPlayerCharacter::Evade);
}

void ACPlayerCharacter::ChangeMovementStrategy(UCMovementStrategy* const NewStrategy)
{
	//
}

void ACPlayerCharacter::Forward(float AxisValue)
{
	//Delegate work to the strategy.
	if (MovementStrategy) MovementStrategy->Forward(AxisValue);
	else UE_LOG(LogTemp,Warning,TEXT("Movement strategy isn't valid."))
}

void ACPlayerCharacter::Right(float AxisValue)
{
	//Delegate work to the strategy.q
	if (MovementStrategy) MovementStrategy->Right(AxisValue);
}

void ACPlayerCharacter::MouseX(float AxisValue)
{
	//Delegate work to the strategy.
}

void ACPlayerCharacter::MouseY(float AxisValue)
{
	//Delegate work to the strategy.
}

void ACPlayerCharacter::RunPressed()
{
	//Delegate work to the strategy.
	if (MovementStrategy) MovementStrategy->RunPressed();
}

void ACPlayerCharacter::RunReleased()
{
	//Delegate work to the strategy.
	if (MovementStrategy) MovementStrategy->RunReleased();
}

void ACPlayerCharacter::Evade()
{
	//Delegate work to the strategy.
	if (MovementStrategy) MovementStrategy->Evade();
}
