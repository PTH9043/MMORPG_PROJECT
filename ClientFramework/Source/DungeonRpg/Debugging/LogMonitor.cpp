// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Debugging/LogMonitor.h"

ULogMonitor::ULogMonitor() {
}

void ULogMonitor::WriteLog(const FString& Message, ELogCategory Category, ELogSeverity Severity)
{
    bool bError = (Severity == ELogSeverity::Error ||  Severity == ELogSeverity::Critical);

    // 카테고리에 맞는 로그를 저장합니다. 
    CollectedLogs[Category].Entries.Emplace(Message, Severity, bError);

    AddLogInternal(Message, GetCategoryString(Category), GetSeverityString(Severity), bError);
}

void ULogMonitor::ExportLogsToCSV(const FString& FileName)
{
    // CSV 헤더 생성
    FString strCSVContent = TEXT("Timestamp,Category,Severity,Message\n");
    for (auto& Pair : CollectedLogs)
    {
        const FString strCategoryName = GetCategoryString(Pair.Key);
        for (const FLogEntry& Entry : Pair.Value.Entries)
        {
            const FString strTimestamp = Entry.Timestamp.ToString();
            const FString strSeverity = GetSeverityString(Entry.eServerity);

            FString EscapedMessage = Entry.strMessage;
            EscapedMessage.ReplaceInline(TEXT("\""), TEXT(""""));
            if (EscapedMessage.Contains(TEXT(",")) || EscapedMessage.Contains(TEXT("\n")))
            {
                EscapedMessage = FString::Printf(TEXT("\"%s\""), *EscapedMessage);
            }
            strCSVContent += FString::Printf(TEXT("%s,%s,%s,%s\n"), *strTimestamp, *strCategoryName, *strSeverity, *EscapedMessage);
        }
        // 로그 제거
        ClearLogs(Pair.Key);
    }
}

void ULogMonitor::ClearLogs(ELogCategory Category)
{
    if (true == CollectedLogs.Contains(Category))
        CollectedLogs[Category].Entries.Empty();
}

void ULogMonitor::AddLogInternal(const FString& Message, const FString& Category, const FString& Severity, bool InError)
{
    if (InError)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s][%s] %s"), *Category, *Severity, *Message);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("[%s][%s] %s"), *Category, *Severity, *Message);
    }
}


FString ULogMonitor::GetCategoryString(ELogCategory Category) const
{
    switch (Category)
    {
    case ELogCategory::System:      return TEXT("System");
    case ELogCategory::Gameplay:  return TEXT("Gameplay");
    case ELogCategory::Combat:      return TEXT("Combat");
    case ELogCategory::AI:                 return TEXT("AI");
    case ELogCategory::Inventory:   return TEXT("Inventory");
    case ELogCategory::UI:                 return TEXT("UI");
    case ELogCategory::Network:     return TEXT("Network");
    case ELogCategory::Custom:      return TEXT("Custom");
    }

    return TEXT("None");
}

FString ULogMonitor::GetSeverityString(ELogSeverity Severity) const
{
    switch (Severity)
    {
    case ELogSeverity::Trace:       return TEXT("Trace");
    case ELogSeverity::Info:           return TEXT("Info");
    case ELogSeverity::Warning: return TEXT("Warning");
    case ELogSeverity::Error:       return TEXT("Error");
    case ELogSeverity::Critical:    return TEXT("Critical");
    }
    return TEXT("None");
}
