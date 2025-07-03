// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Character/DRPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ADRPlayer::ADRPlayer() : 
	pPlayerMappingContext{nullptr}, pMoveAction{nullptr}, pAttackAction{nullptr}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADRPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*
==================================================
		사용자 정의 함수
==================================================
*/

void ADRPlayer::HandleMove(const FInputActionValue& Value)
{
	MoveCharacter(Value.Get<FVector2D>());
}

void ADRPlayer::HandleAttack(const FInputActionValue& Value)
{
}

