// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DungeonRpg/Debugging/LogMonitor.h"

class DUNGEONRPG_API UDRFunction 
{
public:
	static void NullChecker( void* Pointer, UObject* WorldContext, const FString& Message);

	/** 로그를 남기고, 에러일 경우 게임 종료 처리 */
	UFUNCTION(BlueprintCallable, Category = "DungeonRPG|System")
	static void WriteGameLog(UObject* WorldContext, const FString& Message, ELogCategory Category, ELogSeverity Severity);

	
private:
	static void CriticalErrorMessage(const FString& Message);
};