// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Mediators/ActionEventMediator.h"
#include "CDC/Characters/CPlayerCharacter.h"
#include "CDC/Components/CCombatComponent.h"

UActionEventMediator::UActionEventMediator() : UObject()
{
	PlayerCharacter = Cast<ACPlayerCharacter>(GetOuter());
}

void UActionEventMediator::SetCharacter(ACPlayerCharacter* const OUT OutPlayerCharacter)
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

void UActionEventMediator::SetComponent(UCCombatComponent* const OUT OutComponent)
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

void UActionEventMediator::Notify(UObject* const Sender, const FString& Event)
{
	//Extract operations by using Sender and Event; 
}
