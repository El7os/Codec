// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */


struct FDoOnce
{
//	GENERATED_USTRUCT_BODY()
private:
	bool bHasBeenInited = false;

public:

	//Returns true if it haven't done anything already.
	FORCEINLINE bool Do()
	{
		if (!bHasBeenInited)
		{
			bHasBeenInited = true;
			return true;
		}
		return false;
	}

	//Resets FDoOnce node
	FORCEINLINE void Reset() { bHasBeenInited = false; }
};

struct FGate
{
	//GENERATED_USTRUCT_BODY()
private:

	bool bIsGateOpen = false;

public:

	FORCEINLINE bool CanPassThrough() { return bIsGateOpen ? true : false; }
	FORCEINLINE void OpenGate() { bIsGateOpen = true; }
	FORCEINLINE void CloseGate() { bIsGateOpen = false; }
};



class CDC_API StructLibrary
{
public:
	StructLibrary();
	~StructLibrary();
};
