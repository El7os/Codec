// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Movement/Strategies/CMovementStrategy.h"

#include "CDC/Characters/CPlayerCharacter.h"

UCMovementStrategy::UCMovementStrategy() 
	: UObject()
{
	Owner = Cast<ACPlayerCharacter>(GetOuter());
}
