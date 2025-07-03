// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LogMonitor.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ELogCategory : uint8
{
	None			UMETA(DisplayName = "None"),
	System		UMETA(DisplayName = "System"),
	Gameplay	UMETA(DisplayName = "Gameplay"),
	Combat		UMETA(DisplayName = "Combat"),
	AI					UMETA(DisplayName = "AI"),
	Inventory	UMETA(DisplayName = "Inventory"),
	UI					UMETA(DisplayName = "UI"),
	Network		UMETA(DisplayName = "Network"),
	Custom		UMETA(DisplayName = "Custom")
};

UENUM(BlueprintType)
enum class ELogSeverity : uint8
{
	None			UMETA(DisplayName = "None"),
	Trace			UMETA(DisplayName = "Trace"),     // �ſ� ���� ����� ���� (Tick �帧 ��)
	Info				UMETA(DisplayName = "Info"),      // �Ϲ� ����
	Warning		UMETA(DisplayName = "Warning"),   // ���� �ʿ�
	Error			UMETA(DisplayName = "Error"),     // ġ�������� ������ �߸��� ����
	Critical		UMETA(DisplayName = "Critical")  // �ݵ�� ó���ؾ� �� �ɰ��� ���� (ũ���� ����)
};

USTRUCT()
struct FLogEntryContainer
{
	GENERATED_BODY()

	TArray<FLogEntry> Entries;
};

USTRUCT()
struct FLogEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FDateTime				Timestamp;

	UPROPERTY()
	FString						strMessage;

	UPROPERTY()
	ELogSeverity			eServerity;

	UPROPERTY()
	bool							bError;

	FLogEntry() : Timestamp(FDateTime::Now()), strMessage(""),
		 eServerity(ELogSeverity::None), bError(false) { }

	FLogEntry(const FString& InMessage, ELogSeverity InSeverity, bool InError)
		: Timestamp(FDateTime::Now()), strMessage(InMessage), eServerity{ InSeverity }, bError(InError) {}
};

UCLASS()
class DUNGEONRPG_API ULogMonitor : public UObject
{
	GENERATED_BODY()

public:
	ULogMonitor();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void WriteLog(const FString& Message, ELogCategory Category, ELogSeverity Severity);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ExportLogsToCSV(const FString& FileName = TEXT("DebugLogs.csv"));

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void ClearLogs(ELogCategory Category);
private:
	void AddLogInternal(const FString& Message, const FString& Category, const FString& Severity, bool Error);

	FString GetCategoryString(ELogCategory Category) const;
	FString GetSeverityString(ELogSeverity Severity) const;
private:
	UPROPERTY()
	TMap<ELogCategory, FLogEntryContainer>		CollectedLogs;
};
