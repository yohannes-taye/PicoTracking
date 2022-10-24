// Fill out your copyright notice in the Description page of Project Settings.
#include "USBSerialUtil.h"


// Sets default values
AUSBSerialUtil::AUSBSerialUtil()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUSBSerialUtil::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSBSerialUtil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
 
bool AUSBSerialUtil::detectAccessory_new()
{
	bool Result = false;
#if PLATFORM_ANDROID
	Result = AndroidUtils::CallJavaCode<bool>(
	  "com/Plugins/MobileNativeCode/AndroidOpenAccessBridge",
	  "detectAccessory_New",
	  "",
	  true
	);
#endif
	return Result; 
}


FString AUSBSerialUtil::testLocalFunction()
{
	FString Result = TEXT("");
	// return Result; 

	#if PLATFORM_ANDROID
	jobject AndroidOpenAccessBridge = AndroidUtils::CallJavaCode<jobject>(
	  "com/Plugins/MobileNativeCode/AndroidOpenAccessBridge",
	  "getAndroidOpenAccessBrigeInstance",
	  "()Lcom/Plugins/MobileNativeCode/AndroidOpenAccessBridge;",
	  true
	);
	Result = AndroidUtils::CallJavaCode<FString>(
	  AndroidOpenAccessBridge,
	  "testLocalFunction",
	  "",
	  "Test"
	);
	Result = AndroidUtils::CallJavaCode<FString>(
	  AndroidOpenAccessBridge,
	  "getLocalVariable",
	  ""
	);

#endif
	return Result; 
}

FString AUSBSerialUtil::AttachAccessory()
{
	FString Result = TEXT(""); 
#if PLATFORM_ANDROID
	AndroidOpenAccessBridge = AndroidUtils::CallJavaCode<jobject>(
	  "com/Plugins/MobileNativeCode/AndroidOpenAccessBridge",
	  "getAndroidOpenAccessBrigeInstance",
	  "(Landroid/app/Activity;)Lcom/Plugins/MobileNativeCode/AndroidOpenAccessBridge;",
	  true
	);
	
	Result  = AndroidUtils::CallJavaCode<FString>(
		  AndroidOpenAccessBridge,
		  "attachAccessory",
		  ""
	);

#endif
	return Result; 
}

bool AUSBSerialUtil::SendByte(int a)
{
	bool success = false;
#if PLATFORM_ANDROID
	success = AndroidUtils::CallJavaCode<bool>(
		  AndroidOpenAccessBridge,
		  "sendByte",
		  "",
		  a
	);
#endif
	return success;
	
}

