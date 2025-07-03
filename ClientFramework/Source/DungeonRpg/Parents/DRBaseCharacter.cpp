// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonRpg/Parents/DRBaseCharacter.h"

// Sets default values
ADRBaseCharacter::ADRBaseCharacter() : 
	MovementDirection{}, ForwardDirection{}, RightDirection{}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADRBaseCharacter::BeginPlay()
{
}
void ADRBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/* --- 이동 방향 관련 --- */

void ADRBaseCharacter::MoveCharacter(const FVector2D& Direction)
{
	if (nullptr != Controller && false == Direction.IsNearlyZero())
	{
		const FRotator curRotator = Controller->GetControlRotation();
		const FRotator yawRotation{ 0, curRotator.Yaw, 0 };

		ForwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		RightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Direction.Y);
		AddMovementInput(RightDirection, Direction.X);

		MovementDirection = ForwardDirection * Direction.Y + RightDirection * Direction.X;
		MovementDirection.Normalize();
	}
	else
	{
		MovementDirection = FVector::ZeroVector;
	}
}

void ADRBaseCharacter::Attack()
{
}


