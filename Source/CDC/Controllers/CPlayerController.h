// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CDC/Libraries/StructLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
USTRUCT()
struct FInputExtractor
{

	GENERATED_BODY()

	UDELEGATE()
	DECLARE_DELEGATE(NoParamInputActionDelegate);

	UDELEGATE()
	DECLARE_DELEGATE_OneParam(OneParamInputActionDelegate, float);

public:
	FInputExtractor()
	{
	}

	FORCEINLINE void SetPlayerController(APlayerController* const PlayerController) { PC = PlayerController; }
	FORCEINLINE void SetHoverStartThreshold(float NewValue) { HoverStartThreshold = NewValue >= 0.01f ? NewValue : HoverStartThreshold; }

	NoParamInputActionDelegate PressedDelegate;
	NoParamInputActionDelegate DelayedPressedDelegate;
	NoParamInputActionDelegate ReleasedDelegate;
	NoParamInputActionDelegate BeginHoverDelegate;

	OneParamInputActionDelegate OnHoverDelegate;
	OneParamInputActionDelegate EndHoverDelegate;

	void AxisEvent(float AxisValue) 
	{
		if (!AxisValue) return;
		if (!bIsInputTerminated)
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
		Key = OUTKey;
		HoverTime = 0.0f;
		PressedDelegate.ExecuteIfBound();
		Gate_1.OpenGate();
	}

	void ReleasedEvent()
	{
		if (!bIsInputTerminated)
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
			bIsInputTerminated = false;
			DoOnce_2.Reset();
		}

	}


private:


	FDoOnce DoOnce_1;
	FDoOnce DoOnce_2;
	FGate Gate_1;
	FKey Key;
	
	float HoverTime = 0.0f;
	float HoverStartThreshold = 0.3f;
	bool bIsInputTerminated = false;
	
	APlayerController* PC = nullptr;
};


UCLASS()
class CDC_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void BindWeapon(class APlayerWeapon* const Weapon);

	UFUNCTION()
	void UnbindWeapon(class APlayerWeapon* const Weapon);

protected:

	virtual void SetupInputComponent() override;

private:


	UFUNCTION()
	void PrimaryAxisFunc(float AxisValue) { PrimaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void PrimaryActionPressedFunc(FKey Key) { PrimaryInputExtractor.PressedEvent(Key); };

	UFUNCTION()
	void PrimaryActionReleasedFunc() { PrimaryInputExtractor.ReleasedEvent(); };

	UFUNCTION()
	void SecondaryAxisFunc(float AxisValue) { SecondaryInputExtractor.AxisEvent(AxisValue); };

	UFUNCTION()
	void SecondaryActionPressedFunc(FKey Key) { SecondaryInputExtractor.PressedEvent(Key); };

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
	FInputExtractor PrimaryInputExtractor;

	UPROPERTY()
	FInputExtractor SecondaryInputExtractor;

	UPROPERTY()
	FInputExtractor TertiaryInputExtractor;

	UPROPERTY()
	FInputExtractor QuaternaryInputExtractor;
};
