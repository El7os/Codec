// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Mediators/ActionEventMediator.h"
#include "CDC/Characters/CPlayerCharacter.h"
#include "CDC/Components/CCombatComponent.h"

UActionEventMediator::UActionEventMediator() : UObject()
{
	PlayerCharacter = Cast<ACPlayerCharacter>(GetOuter());
}

void UActionEventMediator::SetCharacter(ACPlayerCharacter* const OutPlayerCharacter)
{
	if (OutPlayerCharacter)
	{
		PlayerCharacter = OutPlayerCharacter;
	}
#ifdef WITH_EDITOR
	else
		UE_LOG(LogTemp, Warning, TEXT("Player character cannot be asigned to Action Event Mediator object(&s), player character is null"), *GetName());
#endif // WITH_EDITOR
}

void UActionEventMediator::SetComponent(UCCombatComponent* const OutComponent)
{
	if (OutComponent)
	{
		Component = OutComponent;
	}
#ifdef WITH_EDITOR
	else
		UE_LOG(LogTemp, Warning, TEXT("Component cannot be asigned to Action Event Mediator object(%s), component is null"), *GetName());
#endif
}

void UActionEventMediator::Notify(UObject* const Sender, int num, ...)
{

	using ENotification = ActionEventMediator::Notification;

	va_list VarList;
	va_start(VarList, num);


	for (int i = 0; i < num; i++)
	{
		switch (va_arg(VarList,TEnumAsByte<ENotification>))
		{
		case ENotification::BlockAllInput:

			SetBlockMovement(true);
			SetBlockWeapon(true,false);

			break;
		case ENotification::BlockAllInputByForce:

			SetBlockMovement(true);
			SetBlockWeapon(true, true);

			break;
		case ENotification::BlockMovementOnly:

			SetBlockMovement(true);
		
			break;
		case ENotification::BlockWeaponOnly:

			SetBlockWeapon(true, false);

			break;
		case ENotification::BlockWalkingOnly:

			SetBlockWalking(true);

			break;
		case ENotification::BlockRunningOnly:

			SetBlockRunning(true);

			break;
		case ENotification::BlockEvadeOnly:

			SetBlockEvade(true);

			break;
		case ENotification::BlockSlideOnly:

			SetBlockSlide(true);

			break;
		case ENotification::BlockWeaponOnlyByForce:

			SetBlockWeapon(true, true);

			break;
		case ENotification::UnBlockAllInput:

			SetBlockMovement(false);
			SetBlockWeapon(false, false);

			break;
		case ENotification::UnBlockMovementOnly:

			SetBlockMovement(false);

			break;
		case ENotification::UnBlockWeaponOnly:

			SetBlockWeapon(false, false);

			break;
		case ENotification::UnBlockWalkingOnly:

			SetBlockWalking(false);

			break;
		case ENotification::UnBlockRunningOnly:

			SetBlockRunning(false);

			break;
		case ENotification::UnBlockEvadeOnly:

			SetBlockEvade(false);

			break;
		case ENotification::UnBlockSlideOnly:

			SetBlockSlide(false);

			break;
		}
	}
	va_end(VarList);
}

void UActionEventMediator::SetBlockMovement(bool Block)
{
	SetBlockRunning(Block);
	SetBlockEvade(Block);
	SetBlockWalking(Block);
	SetBlockSlide(Block);
	//if Weapon is valid, block it.
}

void UActionEventMediator::SetBlockRunning(bool Block)
{
	if (PlayerCharacter)
		PlayerCharacter->SetBlockRunningOnly(Block);
}

void UActionEventMediator::SetBlockSlide(bool Block)
{
}

void UActionEventMediator::SetBlockWeapon(bool Block, bool ByForce)
{
	//if Weapon is valid, block it.
}

void UActionEventMediator::SetBlockEvade(bool Block)
{
	if (PlayerCharacter)
		PlayerCharacter->bBlockEvade = Block;
}

void UActionEventMediator::SetBlockWalking(bool Block)
{
	if (PlayerCharacter)
		PlayerCharacter->bBlockWalking = Block;
}
