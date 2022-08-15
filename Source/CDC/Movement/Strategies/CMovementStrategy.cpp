// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CMovementStrategy.h"
#include "CDC/Movement/Mediators/InputMediator.h"
#include "CDC/Characters/CPlayerCharacter.h"

UCMovementStrategy::UCMovementStrategy() : UObject()
{
	Owner = Cast<ACPlayerCharacter>(GetOuter());
	if (Owner)
	{
		InputMediator = Owner->GetGameInstance<UInputMediator>();
	}
}
