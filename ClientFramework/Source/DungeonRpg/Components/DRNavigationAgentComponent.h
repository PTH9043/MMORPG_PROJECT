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

	/* --- ���� �Լ� --- */
protected:
	virtual void BeginPlay() override;
	/* --- ����� ���� �Լ� --- */
public:
	/* ��� ã�� */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool FindPathTo(const FVector& TargetLocation, TArray<FVector>& OutPathPoints);

	/* �ش� ��ġ�� �̵� */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void MoveTo(const FVector& TargetLocation, float AcceptanceRadius = 50.f);

	/* ���� �̵� �ߴ� */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void Stop();

	/* �ش� ��ġ�� �̵� �������� ���� */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool IsNavigable(const FVector& Point) const;

	/* ���� ������ */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetDestination() const { return vDestination; }

	/* --- ����� ���� ���� --- */
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
