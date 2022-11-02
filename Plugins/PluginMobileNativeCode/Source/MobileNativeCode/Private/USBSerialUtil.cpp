// Fill out your copyright notice in the Description page of Project Settings.
#include "USBSerialUtil.h"


// Sets default values
AUSBSerialUtil::AUSBSerialUtil()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AUSBSerialUtil::StaticFunctDispatch(const FString& ReturnValue)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		StaticValueDispatch.ExecuteIfBound(ReturnValue);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ReturnValue);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StaticFunctDispatch"));
	});
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
FTypeDispacth AUSBSerialUtil::StaticValueDispatch;

FString AUSBSerialUtil::AttachAccessory(const FTypeDispacth& CallBackPlatform)
{
	StaticValueDispatch = CallBackPlatform;
	
	FString Result = TEXT(""); 
#if PLATFORM_ANDROID
	AndroidOpenAccessBridge = AndroidUtils::CallJavaCode<jobject>(
	  "com/Plugins/MobileNativeCode/AndroidOpenAccessBridge",
	  "getAndroidOpenAccessBrigeInstance",
	  "(Landroid/app/Activity;)Lcom/Plugins/MobileNativeCode/AndroidOpenAccessBridge;",
	  true
	);
	
	AndroidUtils::CallJavaCode<void>(
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

FString AUSBSerialUtil::SendTrackingData(float tx, float ty, float tz, float rx, float ry, float rz, float rw)
{
	bool success = false;
	FString Result = TEXT("Failed"); 
#if PLATFORM_ANDROID
	Result = AndroidUtils::CallJavaCode<FString>(
		  AndroidOpenAccessBridge,
		  "sendTrackingData",
		  "",
		  tx,
		  ty,
		  tz,
		  rx,
		  ry,
		  rz,
		  rw
	);
#endif
	return Result;
}

//-- Functions CallBack for Java code
#if PLATFORM_ANDROID
JNI_METHOD void Java_com_Plugins_MobileNativeCode_AndroidOpenAccessBridge_CallBackCppAndroid(JNIEnv* env, jclass clazz, jstring returnStr)
{
	FString result = JavaConvert::FromJavaFString(returnStr);
	// UMobileNativeCodeBlueprint::StaticFunctDispatch(result);// Call Dispatcher
	AUSBSerialUtil::StaticFunctDispatch(result);
}
#endif //PLATFORM_ANDROID

