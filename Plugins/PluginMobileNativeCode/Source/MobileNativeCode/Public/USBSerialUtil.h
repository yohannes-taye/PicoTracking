// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FString AttachAccessory();

	UFUNCTION(BlueprintCallable, Category="MobileNativeCode Category", DisplayName="USB Serial Send Byte")
	bool SendByte(int a);

	
};

