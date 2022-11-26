// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CDC/Libraries/StructuresLibrary.h"
#include "GameplayTagContainer.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
USTRUCT()
struct FWeaponInputExtractor
{

	GENERATED_BODY()

public:

	UDELEGATE()
	DECLARE_DELEGATE(NoParamInputActionDelegate)

	UDELEGATE()
	DECLARE_DELEGATE_OneParam(OneParamInputActionDelegate, float)

	FWeaponInputExtractor()
	{
	}

	
	NoParamInputActionDelegate PressedDelegate;
	
	NoParamInputActionDelegate DelayedPressedDelegate;

	NoParamInputActionDelegate ReleasedDelegate;

	NoParamInputActionDelegate BeginHoverDelegate;

	NoParamInputActionDelegate ForceToStopHoverDelegate;
	
	OneParamInputActionDelegate OnHoverDelegate;

	OneParamInputActionDelegate EndHoverDelegate;

	FORCEINLINE void SetPlayerController(APlayerController* const PlayerController) { PC = PlayerController; }

	FORCEINLINE void SetHoverStartThreshold(float NewValue) { HoverStartThreshold = NewValue >= 0.01f ? NewValue : HoverStartThreshold; }

	FORCEINLINE void SetBlockExtraction(bool bOutBlockExtraction) { bBlockExtraction = bBlockExtraction; }

	FORCEINLINE bool GetBlockExtraction() { return bBlockExtraction; }

	void AxisEvent(float AxisValue) 
	{
		if (!AxisValue || bBlockExtraction) return;
		if (!bInputIsTerminated)
		{
			if (Gate_1.CanPassThrough())
			{
				if (PC)
				{
					float KeyDownTime = PC->GetInputKeyTimeDown(Key);
					if (KeyDownTime >= HoverStartThreshold)
					{
						if (DoOnce_1.Do())
							BeginHoverDelegate.ExecuteIfBound();
						HoverTime = KeyDownTime - HoverStartThreshold;
						OnHoverDelegate.ExecuteIfBound(HoverTime);
					}
				}
			}
		}
		else
		{
			if (DoOnce_2.Do())
			{
				Gate_1.CloseGate();
				if (HoverTime > 0)
					EndHoverDelegate.ExecuteIfBound(HoverStartThreshold);
				else
					DelayedPressedDelegate.ExecuteIfBound();
				ReleasedDelegate.ExecuteIfBound();
				DoOnce_1.Reset();
			}	
		}
	}

	void PressedEvent(FKey OUTKey)
	{
		if (bBlockExtraction) return;
		Key = OUTKey;
		HoverTime = 0.0f;
		PressedDelegate.ExecuteIfBound();
		Gate_1.OpenGate();
	}

	void ReleasedEvent()
	{
		if (bBlockExtraction) return;
		if (!bInputIsTerminated)
		{
			Gate_1.CloseGate();
			if (HoverTime > 0)
			{
				EndHoverDelegate.ExecuteIfBound(HoverTime);
			}
			else
			{
				DelayedPressedDelegate.ExecuteIfBound();
			}
			ReleasedDelegate.ExecuteIfBound();
			DoOnce_1.Reset();
		}
		else
		{
			bInputIsTerminated = false;
			DoOnce_2.Reset();
		}

	}


private:

	UPROPERTY()
	APlayerController* PC = nullptr;

	UPROPERTY()
	FDoOnce DoOnce_1;

	UPROPERTY()
	FDoOnce DoOnce_2;

	UPROPERTY()
	FGate Gate_1;

	UPROPERTY()
	FKey Key;
	
	UPROPERTY()
	float HoverTime = 0.0f;

	UPROPERTY()
	float HoverStartThreshold = 0.3f;

	UPROPERTY()
	bool bInputIsTerminated = false;
	
	UPROPERTY()
	bool bBlockExtraction = false;

};

UCLASS()
class CDC_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	DECLARE_DELEGATE(NoParamOnMediatorUpdateDelegate)

	ACPlayerController();

	UFUNCTION()
	void BindWeapon(class APlayerWeapon* const Weapon);

	UFUNCTION()
	void UnbindWeapon(class APlayerWeapon* const Weapon);
	
protected:

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnInputMediatorUpdated(const class UInputMediator* const InputMediator);

	UFUNCTION()
	void PrimaryAxisFunc(float AxisValue) { PrimaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void PrimaryActionPressedFunc(FKey Key) {  PrimaryInputExtractor.PressedEvent(Key); };

	UFUNCTION()
	void PrimaryActionReleasedFunc() {  PrimaryInputExtractor.ReleasedEvent(); };

	UFUNCTION()
	void SecondaryAxisFunc(float AxisValue) { SecondaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void SecondaryActionPressedFunc(FKey Key) {  SecondaryInputExtractor.PressedEvent(Key); };

	UFUNCTION()
	void SecondaryActionReleasedFunc() { SecondaryInputExtractor.ReleasedEvent(); };

	UFUNCTION()
	void TertiaryAxisFunc(float AxisValue) { TertiaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void TertiaryActionPressedFunc(FKey Key) { TertiaryInputExtractor.PressedEvent(Key); };

	UFUNCTION()
	void TertiaryActionReleasedFunc() { TertiaryInputExtractor.ReleasedEvent(); };

	UFUNCTION()
	void QuaternaryAxisFunc(float AxisValue) { QuaternaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void QuaternaryActionPressedFunc(FKey Key) { QuaternaryInputExtractor.PressedEvent(Key); };

	UFUNCTION()
	void QuaternaryActionReleasedFunc() { QuaternaryInputExtractor.ReleasedEvent(); };

	UPROPERTY()
	FWeaponInputExtractor PrimaryInputExtractor;

	UPROPERTY()
	FWeaponInputExtractor SecondaryInputExtractor;

	UPROPERTY()
	FWeaponInputExtractor TertiaryInputExtractor;

	UPROPERTY()
	FWeaponInputExtractor QuaternaryInputExtractor;

	NoParamOnMediatorUpdateDelegate PrimaryAbilityBlockedDelegate;

	NoParamOnMediatorUpdateDelegate SecondaryAbilityBlockedDelegate;

	NoParamOnMediatorUpdateDelegate TertiaryAbilityBlockedDelegate;

	NoParamOnMediatorUpdateDelegate QuaternaryAbilityBlockedDelegate;
};
