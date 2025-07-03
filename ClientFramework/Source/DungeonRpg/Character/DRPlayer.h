// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonRpg/Parents/DRBaseCharacter.h"
#include "InputActionValue.h"
#include "DRPlayer.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class DUNGEONRPG_API ADRPlayer : public ADRBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADRPlayer();

	/* �𸮾� ���� �Լ� */
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* ����� ���� �Լ�*/
public:
	void HandleMove(const FInputActionValue& Value);
	void HandleAttack(const FInputActionValue& Value);

	/* get set */
public:


private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext>			pPlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction>								pMoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction>								pAttackAction;


};
