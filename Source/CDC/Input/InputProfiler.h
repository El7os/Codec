// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RawInputFunctionLibrary.h"
#include "Misc/CoreMiscDefines.h"
#include "InputProfiler.generated.h"

#define ARCHIVE_PATH 

namespace InputProfiler
{
	UENUM()
	enum class EControllerDeviceType : uint8
	{
		EControllerType_Null UMETA(DisplayName = "Null", Tooltip = "Undeterminated controller") = 0,
		EControllerType_Keyboard UMETA(DisplayName = "Keyboard"),
		EControllerType_Gameplad UMETA(DisplayName = "Gamepad"),
		EControllerType_FlightStick UMETA(DisplayName = "FlightStick"),
		EControllerType_SteeringWheel UMETA(DisplayName = "SteeringWheel")
	};

	struct ArchiveEntry
	{
		InputProfiler::EControllerDeviceType DeviceType = InputProfiler::EControllerDeviceType::EControllerType_Null;

		int32 VendorID = 0x000;

		int32 ProductID = 0x000;

		FName CompanyName = NAME_None;

		FName InputType = NAME_None;
	};

}



/**
 * 
 */
UCLASS()
class CDC_API UInputProfiler : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UInputProfiler();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;


	/*void UpdateProfiler();

	void UpdateConnectedDevices();*/
	
	void FetchArchive(const FName& Path);

	TMap<InputProfiler::EControllerDeviceType, TArray<FRegisteredDeviceInfo>> Devices;
	
	TMap<TPair<int32, int32>, InputProfiler::ArchiveEntry> Archive;

};
