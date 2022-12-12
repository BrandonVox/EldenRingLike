// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EldenCharacter.h"
#include "PlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ELDENRINGLIKE_API APlayerCharacter : public AEldenCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	* Target Interface
	*/
	virtual FVector EndLocationToFindTarget() override;

protected:
	/*
	* Action Pressed
	*/
	void AttackButtonPressed();
	void ChargeAttackButtonPressed();
	void RollButtonPressed();
	void TargetButtonPressed();
	void TestDeflectButtonPressed();
	/*
	* Axes
	*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

private:
	/*
	* Camera
	*/
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;
};
