// Fill out your copyright notice in the Description page of Project Settings.


#include "CDC/Input/InputProfiler.h"
#include "RawInput.h"
#include "RawInputFunctionLibrary.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include "Misc/CoreDelegates.h"
#include "Subsystems/GameInstanceSubsystem.h"


UInputProfiler::UInputProfiler() : UGameInstanceSubsystem()
{
}

void UInputProfiler::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	IRawInput* RawInput = FRawInputPlugin::Get().GetRawInputDevice().Get();
	if (RawInput)
	{
		RawInput->QueryConnectedDevices();

		for (const FRegisteredDeviceInfo& DeviceInfo : URawInputFunctionLibrary::GetRegisteredDevices())
		{
			UE_LOG(LogTemp, Warning, TEXT("============="));
			UE_LOG(LogTemp, Warning, TEXT("Device Name : %s"), *DeviceInfo.DeviceName);
			UE_LOG(LogTemp, Warning, TEXT("Device VID : %i"), DeviceInfo.VendorID);
			UE_LOG(LogTemp, Warning, TEXT("Device PID : %i"), DeviceInfo.ProductID);
			UE_LOG(LogTemp, Warning, TEXT("============="));
		}
	}



}

void UInputProfiler(const FName& Path)
{

}