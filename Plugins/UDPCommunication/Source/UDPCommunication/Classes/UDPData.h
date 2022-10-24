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
	return Ar;
}