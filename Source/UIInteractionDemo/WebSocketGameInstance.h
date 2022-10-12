// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IWebSocket.h"
#include "Engine/GameInstance.h"
#include "WebSocketGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UIINTERACTIONDEMO_API UWebSocketGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category="Custom")
	void SendMessage(FString message);
	
	TSharedPtr<IWebSocket> WebSocket;
};
