// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StructuresLibrary.generated.h"

USTRUCT()
struct FDoOnce
{
	GENERATED_BODY()

public:

	FORCEINLINE bool Do()
	{
		if (!bHasBeenInited)
		{
			bHasBeenInited = true;
			return true;
		}
		return false;
	}

	FORCEINLINE void Reset() { bHasBeenInited = false; }

private:

	UPROPERTY()
	bool bHasBeenInited = false;

};

USTRUCT()
struct FGate
{
	
	GENERATED_BODY()
public:

	FORCEINLINE bool CanPassThrough() { return bIsGateOpen ? true : false; }
	FORCEINLINE void OpenGate() { bIsGateOpen = true; }
	FORCEINLINE void CloseGate() { bIsGateOpen = false; }

private:

	UPROPERTY()
	bool bIsGateOpen = false;
};


/**
 * 
 */
UCLASS()
class CDC_API UStructuresLibrary : public UObject
{
	GENERATED_BODY()
	
};
