// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Characters/CCharacter.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

