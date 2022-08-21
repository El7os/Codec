// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Weapons/PlayerWeapons/IronClaw.h"


void AIronClaw::PrimaryPressed()
{
	Super::PrimaryPressed();

	UE_LOG(LogTemp, Warning, TEXT("Iron Claw primary pressed"));
}

void AIronClaw::PrimaryDelayedPressed()
{
	Super::PrimaryDelayedPressed();
	UE_LOG(LogTemp, Warning, TEXT("Iron Claw primary delayed pressed"));
}

void AIronClaw::PrimaryBeginHover()
{
	Super::PrimaryBeginHover();
	UE_LOG(LogTemp, Warning, TEXT("Iron Claw primary begin hover"));
}

void AIronClaw::PrimaryOnHover(float ElapsedTime)
{
	Super::PrimaryOnHover(ElapsedTime);
	UE_LOG(LogTemp, Warning, TEXT("Iron Claw elapsed time %f"), ElapsedTime);
}

void AIronClaw::PrimaryEndHover(float TotalTime)
{
	Super::PrimaryEndHover(TotalTime);
	UE_LOG(LogTemp, Warning, TEXT("Iron Claw total time %f"), TotalTime);
}

void AIronClaw::PrimaryReleased()
{
	Super::PrimaryReleased();
	UE_LOG(LogTemp, Warning, TEXT("Iron Claw primary released"));
}

void AIronClaw::OnPrimaryInputBlocked()
{
	Super::OnPrimaryInputBlocked();
}