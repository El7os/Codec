// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Characters/CPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"
#include "CDC/Movement/Mediators/InputMediator.h"
#include "CDC/Components/CCombatComponent.h"


ACPlayerCharacter::ACPlayerCharacter() 
	: ACCharacter()
	, ForwardAxisInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Forward")))
	, RightAxisInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Right")))
	, Action1InputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Action1")))
	, Action2InputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Action2")))
	, MouseXInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.MouseX")))
	, MouseYInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.MouseY")))
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

	InputMediator = GetGameInstance()->GetSubsystem<UInputMediator>();
}

UAbilitySystemComponent* ACPlayerCharacter::GetAbilitySystemComponent() const
{
	return CombatComponent;
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ACPlayerCharacter::Forward);
		PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACPlayerCharacter::Right);
		PlayerInputComponent->BindAction(TEXT("Action1"), IE_Pressed, this, &ACPlayerCharacter::Action1Pressed);
		PlayerInputComponent->BindAction(TEXT("Action1"), IE_Released, this, &ACPlayerCharacter::Action1Released);
		PlayerInputComponent->BindAction(TEXT("Action2"), IE_Pressed, this, &ACPlayerCharacter::Action2Pressed);
		PlayerInputComponent->BindAction(TEXT("Action2"), IE_Released, this, &ACPlayerCharacter::Action2Released);

	}
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
	if (MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(ForwardAxisInputBlockerTag))
		MovementStrategy->Forward(AxisValue);
}

void ACPlayerCharacter::Right(float AxisValue)
{
	if (MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(RightAxisInputBlockerTag))
		MovementStrategy->Right(AxisValue);
}

void ACPlayerCharacter::MouseX(float AxisValue)
{
	//Delegate work to the strategy.
}

void ACPlayerCharacter::MouseY(float AxisValue)
{
	//Delegate work to the strategy.
}

void ACPlayerCharacter::Action1Pressed()
{
	if (MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(Action1InputBlockerTag))
		MovementStrategy->Action1Pressed();
}

void ACPlayerCharacter::Action1Released()
{
	if (MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(Action1InputBlockerTag))
		MovementStrategy->Action1Released();	
}

void ACPlayerCharacter::Action2Pressed()
{
	if (MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(Action2InputBlockerTag))
		MovementStrategy->Action2Pressed();
}

void ACPlayerCharacter::Action2Released()
{
	if(MovementStrategy && InputMediator && !InputMediator->GetTags().HasTag(Action2InputBlockerTag))
		MovementStrategy->Action2Released();
}