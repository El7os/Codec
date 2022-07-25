// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionEventMediator.generated.h"

/**
 * 
 */
UCLASS()
class CDC_API UActionEventMediator : public UObject
{
	GENERATED_BODY()
	
public:

	UActionEventMediator();

	UFUNCTION(BlueprintCallable)
	void SetCharacter(class ACPlayerCharacter* const OutPlayerCharacter);

	/*void SetComponent(class UCombatComponent* const Component);*/

	//void SetWeapon(class ACPlayerWeapon* const PlayerWeapon);
	
	UFUNCTION(BlueprintCallable)
	void Notify(UObject* const Sender, const FString& Event);
private:

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ACPlayerCharacter* PlayerCharacter;

	/*class UCombatComponent* Component;*/

	//class ACPlayerWeapon* PlayerWeapon;
};
