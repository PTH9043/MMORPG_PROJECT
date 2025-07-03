// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Components/DRNavigationAgentComponent.h"
#include <NavigationSystem.h>
#include "GameFramework/Character.h"
#include "AIController.h"
#include "DungeonRpg/Utility/DRFuncton.h"

// Sets default values for this component's properties
UDRNavigationAgentComponent::UDRNavigationAgentComponent() : 
	pOwnerCharacter{nullptr},
	pNavigationSystem{nullptr},
	bNavigating{false}
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDRNavigationAgentComponent::BeginPlay()
{
	pOwnerCharacter = Cast<ACharacter>(GetOwner());
	pNavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	UDRFunction::NullChecker(pOwnerCharacter.Get(), this, "OwnerCharacter is nullptr");
	UDRFunction::NullChecker(pNavigationSystem.Get(), this, "NavigationSystem is nullptr");
}

bool UDRNavigationAgentComponent::FindPathTo(const FVector& TargetLocation, TArray<FVector>& OutPathPoints)
{
	UNavigationPath* Path = pNavigationSystem->FindPathToLocationSynchronously(GetWorld(), pOwnerCharacter->GetActorLocation(), TargetLocation, pOwnerCharacter.Get());
	if (Path && Path->IsValid())
	{
		OutPathPoints = Path->PathPoints;
		return true;
	}

	return false;
}

void UDRNavigationAgentComponent::MoveTo(const FVector& TargetLocation, float AcceptanceRadius)
{
	vDestination = TargetLocation;
	bNavigating = true;

	AController* Ctrl = pOwnerCharacter->GetController();
	if (nullptr != Ctrl)
	{
		AAIController* AI = Cast<AAIController>(Ctrl);
		if (nullptr != AI)
		{
			AI->MoveToLocation(TargetLocation, AcceptanceRadius, true, true, true, false, 0, true);
		}
	}
	else
	{
		// 플레이어일 경우 직접 방향 입력
		FVector Dir = (TargetLocation - pOwnerCharacter->GetActorLocation()).GetSafeNormal();
		pOwnerCharacter->AddMovementInput(Dir);
	}
}

void UDRNavigationAgentComponent::Stop()
{
}

bool UDRNavigationAgentComponent::IsNavigable(const FVector& Point) const
{
	return false;
}

