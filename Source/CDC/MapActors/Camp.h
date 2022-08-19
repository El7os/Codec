// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camp.generated.h"

UCLASS()
class CDC_API ACamp : public AActor
{
	GENERATED_BODY()
	
public:	
	ACamp();
	
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Interaction"))
	void BP_OnInteracted();

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class APlayerWeapon>> Weapons;



};
