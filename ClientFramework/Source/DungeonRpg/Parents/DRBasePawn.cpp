// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Parents/DRBasePawn.h"

// Sets default values
ADRBasePawn::ADRBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADRBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADRBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

