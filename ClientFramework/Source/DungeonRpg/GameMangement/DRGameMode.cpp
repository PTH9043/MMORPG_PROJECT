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
		// ���� ����(��������)�� �̸� ��������
		const FString LevelName = GetWorld()->GetMapName();

		// PIE������ ���ξ ���� �� ������ ����
		FString SanitizedLevelName = FPackageName::GetShortName(LevelName);

		FString FinalFileName = FString::Printf(TEXT("..\\ExportedLogs\\%s_LogDatas.csv"), *SanitizedLevelName); // �� ����� ���޵�

		pLogMonitor->ExportLogsToCSV(FinalFileName);
	}
}

void ADRGameMode::WriteLog(const FString& Message, ELogCategory Category, ELogSeverity Severity)
{
	if (nullptr != pLogMonitor)
		pLogMonitor->WriteLog(Message, Category, Severity);
}

