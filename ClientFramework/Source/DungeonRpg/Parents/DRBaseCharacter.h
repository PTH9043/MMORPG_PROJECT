// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRBaseCharacter.generated.h"

UCLASS()
class DUNGEONRPG_API ADRBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADRBaseCharacter();

	/* �𸮾� ���� �Լ� */
protected:
	virtual void BeginPlay() override;
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* --- ���� ĳ���� ���� --- */
protected:
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void MoveCharacter(const FVector2D& Direction);

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void Attack();

	/* --- �̵� ���� ���� --- */
	/* get set*/
public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetMovementDirection() const { return MovementDirection; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetForwardDirection() const { return ForwardDirection; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FVector GetRightDirection() const { return RightDirection; }

protected:
	UFUNCTION(BlueprintCallable, Category = "Movement")

	void SetMovementDirection(const FVector& Direction) { this->MovementDirection = Direction; }
	UFUNCTION(BlueprintCallable, Category = "Movement")

	void SetForwardDirection(const FVector& Direction) { this->ForwardDirection = Direction; }
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetRightDirection(const FVector& Direction) { this->RightDirection = Direction; }
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector					MovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector					ForwardDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector					RightDirection;

};
