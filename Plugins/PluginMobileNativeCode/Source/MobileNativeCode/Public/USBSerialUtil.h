// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileNativeCodeBlueprint.h"
#include "GameFramework/Actor.h"
#if PLATFORM_ANDROID
#include "Android/Utils/AndroidUtils.h"
#endif

#include "USBSerialUtil.generated.h"

UCLASS()
class MOBILENATIVECODE_API AUSBSerialUtil : public AActor
{
	GENERATED_BODY()

	
public:
	// Sets default values for this actor's properties
	AUSBSerialUtil();
	
	static FTypeDispacth StaticValueDispatch;
	static void StaticFunctDispatch(const FString& ReturnValue);

	static FTypeDispacth StaticValueDispatch_SendArray;
	static void StaticFunctDispatch_SendArray(const FString& ReturnValue);



private:
#if PLATFORM_ANDROID
	jobject AndroidOpenAccessBridge;
#endif
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MobileNativeCode Category", DisplayName="USB Serial Detect Accessory")
	static bool detectAccessory_new();

	UFUNCTION(BlueprintCallable, Category = "MobileNativeCode Category",DisplayName="USB Serial Test Local Function")
	static FString testLocalFunction();

	UFUNCTION(BlueprintCallable, Category = "MobileNativeCode Category",DisplayName="USB Serial Attach Accessory")
	FString AttachAccessory(const FTypeDispacth& CallBackPlatform);

	UFUNCTION(BlueprintCallable, Category="MobileNativeCode Category", DisplayName="USB Serial Send Byte")
	bool SendByte(int a);

	UFUNCTION(BlueprintCallable, Category="MobileNativeCode Category", DisplayName="USB Serial Send Tracking Data")
	FString SendTrackingData(const FTypeDispacth& CallBackPlatform, float tx, float ty, float tz, float rx, float ry, float rz, float rw);

	
};

