#pragma once

#include "Serialization/Archive.h"
#include "UDPData.generated.h"

USTRUCT(BlueprintType)
struct FUDPData {
	GENERATED_USTRUCT_BODY()
	int header1 = 0x0100f8f8;
	unsigned char a0 = 0xa0;
	unsigned char a1 = 0xa1;
	unsigned char a2 = 0xa2;
	unsigned char a7 = 0xa7;
	unsigned char a8 = 0xa8;
	unsigned char a9 = 0xa9;
	unsigned char aa = 0xaa;
	unsigned char blank = 0.0f;
	unsigned char PacketSize = 0x07; 
	

	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float1 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float2 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float3 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float4 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float5 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float6 = 0.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	float float7 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	int64 float8 = 0.0f; 
	// int32 float8 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float9 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float10 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float11 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float12 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float13 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float14 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float15 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float16 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float17 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float18 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float19 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	float float20 = 0.0f;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	uint8 uint1 = 0;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	uint8 uint2 = 0;
	// UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "UDPCommunication")
	// 	uint8 uint3 = 0;
	FUDPData() {
	}
};
FORCEINLINE float ReverseFloat2( const float inFloat )
{
	float retVal;
	char *floatToConvert = ( char* ) & inFloat;
	char *returnFloat = ( char* ) & retVal;

	// swap the bytes into a temporary buffer
	returnFloat[0] = floatToConvert[3];
	returnFloat[1] = floatToConvert[2];
	returnFloat[2] = floatToConvert[1];
	returnFloat[3] = floatToConvert[0];

	return retVal;
}
FORCEINLINE FArchive& operator<<(FArchive &Ar, FUDPData &Structure)
{

	FDateTime Time = FDateTime::Now();
	Structure.float8=Time.ToUnixTimestamp();
	// Structure.float1 = 0.0f;
	// FString converted_text= FString::Printf(TEXT("%lld"), Structure.float8);
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *converted_text);	
	// Structure.float1 = ReverseFloat2(Structure.float1);
	// Structure.float2 = ReverseFloat2(Structure.float2);
	// Structure.float3 = ReverseFloat2(Structure.float3); 
	Ar << Structure.header1;
	Ar << Structure.float8;
	Ar << Structure.PacketSize; 
	Ar << Structure.a0;
	Ar << Structure.float1;
	Ar << Structure.a1; 
	Ar << Structure.float2;
	Ar << Structure.a2; 
	Ar << Structure.float3;
	Ar << Structure.a7; 
	Ar << Structure.float4;
	Ar << Structure.a8; 
	Ar << Structure.float5;
	Ar << Structure.a9; 
	Ar << Structure.float6;
	Ar << Structure.aa; 
	Ar << Structure.float7;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	//
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;
	// Ar << Structure.blank;

	return Ar;
}