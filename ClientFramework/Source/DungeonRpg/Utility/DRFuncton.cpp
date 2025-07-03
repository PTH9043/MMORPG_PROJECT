// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Utility/DRFuncton.h"
#include "DungeonRpg/GameMangement/DRGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Misc/OutputDeviceNull.h"

void UDRFunction::NullChecker(void* Pointer, UObject* WorldContext, const FString& Message)
{
	if (nullptr == Pointer)
	{
		WriteGameLog(WorldContext, Message, ELogCategory::System, ELogSeverity::Critical);
		return;
	}
}

void UDRFunction::WriteGameLog(UObject* WorldContext, const FString& Message, ELogCategory Category, ELogSeverity Severity)
{
	if (!WorldContext)
	{
		CriticalErrorMessage(TEXT("WorldContext is Nullptr"));
		return;
	}

	UWorld* World = WorldContext->GetWorld();
	if (!World)
	{
		CriticalErrorMessage(TEXT("World is Nullptr"));
		return;
	}

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	ADRGameMode* DRGameMode = Cast<ADRGameMode>(GameMode);

	if (nullptr == DRGameMode)
	{
		CriticalErrorMessage(TEXT("DRGameMode Cast Failed"));
		return;
	}

	DRGameMode->WriteLog(Message, Category, Severity);

	// 에러 심각도 이상이면 즉시 종료
	if (Severity == ELogSeverity::Warning || Severity == ELogSeverity::Trace) return;
	CriticalErrorMessage(Message);
}

void UDRFunction::CriticalErrorMessage(const FString& Message)
{
	UE_LOG(LogTemp, Error, TEXT("Critical Error: %s"), *Message);
	FPlatformMisc::RequestExit(false); // false = soft exit (graceful)
}
