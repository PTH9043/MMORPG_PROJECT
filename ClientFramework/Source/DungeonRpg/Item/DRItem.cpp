// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Item/DRItem.h"

// Sets default values
ADRItem::ADRItem()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADRItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADRItem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

