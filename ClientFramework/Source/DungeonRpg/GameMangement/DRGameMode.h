// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonRpg/Debugging/LogMonitor.h"
#include "DRGameMode.generated.h"


UCLASS()
class DUNGEONRPG_API ADRGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADRGameMode();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public: /* Log Monitor */
	void WriteLog(const FString& Message, ELogCategory Category, ELogSeverity Severity);

private:
	UPROPERTY()
	TObjectPtr<ULogMonitor>			pLogMonitor;
};
