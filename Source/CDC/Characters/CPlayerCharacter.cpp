// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Characters/CPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"
#include "CDC/Movement/Mediators/ActionEventMediator.h"
#include "CDC/Components/CCombatComponent.h"

ACPlayerCharacter::ACPlayerCharacter() : ACCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800.0f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 110.0f;

	CombatComponent = CreateDefaultSubobject<UCCombatComponent>(TEXT("Combat Component"));
}

void ACPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (InitialMovementStrategyClass)
	{
		MovementStrategy = NewObject<UCMovementStrategy>(this, InitialMovementStrategyClass);
	}
	else
	{
		MovementStrategy = NewObject<UCDefaultMovementStrategy>(this);
#ifdef WITH_EDITOR
		UE_LOG(LogTemp,Warning,TEXT("Movement strategy class isn't valid. It assumed default"))
#endif // WITH_EDITOR
	}
		
	EventMediator = NewObject<UActionEventMediator>(this);
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CombatComponent)
		CombatComponent->InitAbilityActorInfo(this, this);
#ifdef WITH_EDITOR
	else
		UE_LOG(LogTemp, Warning, TEXT("Ability System Component is null (%s)"), *GetName());
#endif

	if (EventMediator)
	{
		EventMediator->SetComponent(CombatComponent);
	}
}

UAbilitySystemComponent* ACPlayerCharacter::GetAbilitySystemComponent() const
{
	return CombatComponent;
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
	if (NewStrategy)
	{
		if (MovementStrategy)
			MovementStrategy->MarkAsGarbage();
		MovementStrategy = NewStrategy;
	}
#ifdef WITH_EDITOR
	else
		UE_LOG(LogTemp,Warning,TEXT("Movement Strategy couldn't be changed, new strategy is null."))
#endif // WITH_EDITOR

}

void ACPlayerCharacter::Forward(float AxisValue)
{
	//Delegate work to the strategy.
	if (MovementStrategy && !bBlockWalking) MovementStrategy->Forward(AxisValue);
}

void ACPlayerCharacter::Right(float AxisValue)
{
	//Delegate work to the strategy.
	if (MovementStrategy && !bBlockWalking) MovementStrategy->Right(AxisValue);
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
	if (MovementStrategy && !bBlockRunning) MovementStrategy->RunPressed();
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
