// Fill out your copyright notice in the Description page of Project Settings.


#include "TMCFIleController.h"



FString UTMCFIleController::LoadFileToString(FString FileName)
{
	// FString Directory = FPaths::LaunchDir();
	FString Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();
	FString Directory = "/storage/emulated/0/"; 
	if(File.DirectoryExists(*Directory))
	{
		UE_LOG(LogTemp, Warning, TEXT("LALI_LOG: Director exists! Attempting to read file."));

		// FString MyFile = Directory + "/" + FileName;
		FString MyFile = "/storage/emulated/0/tmc.txt";
		bool ReadStatus = FFileHelper::LoadFileToString(Result, *MyFile);
		if(ReadStatus)
		{
			UE_LOG(LogTemp, Warning, TEXT("LALI_LOG: Reading Successful!"));
		}
		else{
			UE_LOG(LogTemp, Error, TEXT("LALI_LOG: (1) Unable to read file!"));
		
		}
		return Result; 
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("LALI_LOG: (2) Unable to read file!"));

	}

	
	return "EMPTY"; 
}

bool UTMCFIleController::CreateFileAndSave(FString FileName)
{
	//LaunchDir
	//RootDir
	FString Directory = FPaths::LaunchDir();
	// FString Result;
	IPlatformFile& File = FPlatformFileManager::Get().GetPlatformFile();
	if(File.CreateDirectory(*Directory))
	{
		FString MyFile = Directory + "/" + FileName;
		// FFileHelper::LoadFileToString(Result, *MyFile);
		return FFileHelper::SaveStringToFile(TEXT("Sample text"), *MyFile);
	}
	return false; 
	
}

