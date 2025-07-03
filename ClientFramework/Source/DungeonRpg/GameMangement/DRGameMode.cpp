// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/GameMangement/DRGameMode.h"

ADRGameMode::ADRGameMode() : pLogMonitor{nullptr}
{
}

void ADRGameMode::BeginPlay()
{
	pLogMonitor = NewObject<ULogMonitor>(this, ULogMonitor::StaticClass());
}

void ADRGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (pLogMonitor)
	{
		// 현재 월드(스테이지)의 이름 가져오기
		const FString LevelName = GetWorld()->GetMapName();

		// PIE에서는 접두어가 붙을 수 있으니 제거
		FString SanitizedLevelName = FPackageName::GetShortName(LevelName);

		FString FinalFileName = FString::Printf(TEXT("..\\ExportedLogs\\%s_LogDatas.csv"), *SanitizedLevelName); // ← 여기로 전달됨

		pLogMonitor->ExportLogsToCSV(FinalFileName);
	}
}

void ADRGameMode::WriteLog(const FString& Message, ELogCategory Category, ELogSeverity Severity)
{
	if (nullptr != pLogMonitor)
		pLogMonitor->WriteLog(Message, Category, Severity);
}

