// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Weapons/PlayerWeapons/ElementalSpear.h"


void AElementalSpear::PrimaryPressed()
{
	Super::PrimaryPressed();

	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear primary pressed"));
}

void AElementalSpear::PrimaryDelayedPressed()
{
	Super::PrimaryDelayedPressed();
	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear primary delayed pressed"));
}

void AElementalSpear::PrimaryBeginHover()
{
	Super::PrimaryBeginHover();
	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear primary begin hover"));
}

void AElementalSpear::PrimaryOnHover(float ElapsedTime)
{
	Super::PrimaryOnHover(ElapsedTime);
	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear elapsed time %f"), ElapsedTime);
}

void AElementalSpear::PrimaryEndHover(float TotalTime)
{
	Super::PrimaryEndHover(TotalTime);
	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear total time %f"), TotalTime);
}

void AElementalSpear::PrimaryReleased()
{
	Super::PrimaryReleased();
	UE_LOG(LogTemp, Warning, TEXT("Elemental Spear primary released"));
}

void AElementalSpear::OnPrimaryInputBlocked()
{
	Super::OnPrimaryInputBlocked();
}