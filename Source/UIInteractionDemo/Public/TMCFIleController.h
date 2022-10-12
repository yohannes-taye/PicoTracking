// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TMCFIleController.generated.h"

/**
 * 
 */
UCLASS()
class UIINTERACTIONDEMO_API UTMCFIleController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Custom")
	static FString LoadFileToString(FString FileName);

	UFUNCTION(BlueprintCallable, Category="Custom")
	static bool CreateFileAndSave(FString FileName); 
};
