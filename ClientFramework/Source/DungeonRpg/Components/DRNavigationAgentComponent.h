// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigationPath.h"
#include "DRNavigationAgentComponent.generated.h"

class ACharacter;
class UNavigationSystemV1;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRPG_API UDRNavigationAgentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDRNavigationAgentComponent();

	/* --- 엔진 함수 --- */
protected:
	virtual void BeginPlay() override;
	/* --- 사용자 정의 함수 --- */
public:
	/* 경로 찾기 */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool FindPathTo(const FVector& TargetLocation, TArray<FVector>& OutPathPoints);

	/* 해당 위치로 이동 */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void MoveTo(const FVector& TargetLocation, float AcceptanceRadius = 50.f);

	/* 현재 이동 중단 */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void Stop();

	/* 해당 위치로 이동 가능한지 여부 */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool IsNavigable(const FVector& Point) const;

	/* 현재 목적지 */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetDestination() const { return vDestination; }

	/* --- 사용자 정의 변수 --- */
private:
	UPROPERTY()
	FVector															vDestination;

	UPROPERTY()
	TObjectPtr<ACharacter>							pOwnerCharacter;

	UPROPERTY()
	TObjectPtr<UNavigationSystemV1>		pNavigationSystem;

	UPROPERTY()
	bool																bNavigating;
};
