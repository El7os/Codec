// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/MapActors/Camp.h"

// Sets default values
ACamp::ACamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

