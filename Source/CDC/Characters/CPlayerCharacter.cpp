// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Characters/CPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CDC/Movement/Strategies/CDefaultMovementStrategy.h"
#include "CDC/Movement/Mediators/InputMediator.h"
#include "CDC/Components/CCombatComponent.h"


ACPlayerCharacter::ACPlayerCharacter() 
	: ACCharacter()
	, ForwardInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Forward")))
	, RightInputBlockerTag(FGameplayTag::RequestGameplayTag(TEXT("Control.Block.Input.Right")))
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
	if (InputMediator)
		InputMediator->MediatorUpdateBroadcast.AddUObject(this, &ACPlayerCharacter::OnInputMediatorUpdated);
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

void ACPlayerCharacter::OnInputMediatorUpdated()
{
	if (InputMediator)
	{
		LastForwardInputQueryResult = !InputMediator->GetTags().HasTag(ForwardInputBlockerTag);
		LastRightInputQueryResult = !InputMediator->GetTags().HasTag(RightInputBlockerTag);
		LastAction1InputQueryResult = !InputMediator->GetTags().HasTag(Action1InputBlockerTag);
		LastAction2InputQueryResult = !InputMediator->GetTags().HasTag(Action2InputBlockerTag);
		LastMouseXInputQueryResult = !InputMediator->GetTags().HasTag(MouseXInputBlockerTag);
		LastMouseYInputQueryResult = !InputMediator->GetTags().HasTag(MouseYInputBlockerTag);

		if (MovementStrategy)
		{
			if (bIsAction1Active && !LastAction1InputQueryResult)
			{
				MovementStrategy->ForceAction1ToStop();
				bIsAction1Active = false;
			}
				
			if (bIsAction2Active && !LastAction2InputQueryResult)
			{
				MovementStrategy->ForceAction2ToStop();
				bIsAction1Active = false;
			}
				

		}
		
	}
}

void ACPlayerCharacter::Forward(float AxisValue)
{
	//Delegate work to the strategy.
	if (InputMediator && MovementStrategy)
	{
		if (LastForwardInputQueryResult)
			MovementStrategy->Forward(AxisValue);
	}
}

void ACPlayerCharacter::Right(float AxisValue)
{
	//Delegate work to the strategy.
	if (InputMediator && MovementStrategy)
	{
		if (LastRightInputQueryResult)
			MovementStrategy->Right(AxisValue);
	}
}

void ACPlayerCharacter::MouseX(float AxisValue)
{
	//Delegate work to the strategy.
	if (InputMediator && MovementStrategy)
	{
		if (LastMouseXInputQueryResult)
			MovementStrategy->MouseX(AxisValue);
	}
}

void ACPlayerCharacter::MouseY(float AxisValue)
{
	//Delegate work to the strategy.
	if (InputMediator && MovementStrategy)
	{
		if (LastMouseYInputQueryResult)
			MovementStrategy->MouseY(AxisValue);
	}
}

void ACPlayerCharacter::Action1Pressed()
{
	//Delegate work to the strategy
	if (InputMediator && MovementStrategy)
	{
		if (LastAction1InputQueryResult)
		{
			bIsAction1Active = true;
			MovementStrategy->Action1Pressed();
		}
	}
}

void ACPlayerCharacter::Action1Released()
{
	//Delegate work to the strategy
	if (InputMediator && MovementStrategy)
	{
		if (LastAction1InputQueryResult && bIsAction1Active)
		{
			MovementStrategy->Action1Released();
			bIsAction1Active = false;
		}
	}
}

void ACPlayerCharacter::Action2Pressed()
{
	//Delegate work to the strategy
	if (InputMediator && MovementStrategy)
	{
		if (LastAction2InputQueryResult)
		{
			MovementStrategy->Action2Pressed();
			bIsAction2Active = true;
		}
	}
}

void ACPlayerCharacter::Action2Released()
{
	//Delegate work to the strategy
	if (InputMediator && MovementStrategy)
	{
		if (LastAction2InputQueryResult && bIsAction2Active)
		{
			bIsAction2Active = false;
			MovementStrategy->Action2Released();
		}
	}
}