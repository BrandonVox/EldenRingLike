// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EldenRingLike/CustomComponents/TargetComponent.h"
#include "EldenRingLike/CustomComponents/CombatComponent.h"
#include "EldenRingLike/AnimInstances/EldenAnimInstance.h"

APlayerCharacter::APlayerCharacter()
{
	/*
	* Camera
	*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ACharacter::SetupPlayerInputComponent(PlayerInputComponent);
	/*
	* Action Pressed
	*/
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEldenCharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("ChargeAttack", IE_Pressed, this, &APlayerCharacter::ChargeAttackButtonPressed);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::RollButtonPressed);
	PlayerInputComponent->BindAction("Target", IE_Pressed, this, &APlayerCharacter::TargetButtonPressed);
	PlayerInputComponent->BindAction("Guard", IE_Pressed, this, &APlayerCharacter::GuardButtonPressed);
	PlayerInputComponent->BindAction("TestDeflect", IE_Pressed, this, &APlayerCharacter::TestDeflectButtonPressed);
	/*
	* Axes
	*/
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
}

FVector APlayerCharacter::EndLocationToFindTarget()
{
	if (FollowCamera == nullptr || TargetComponent == nullptr)
	{
		return GetActorLocation();
	}

	return GetActorLocation() + FollowCamera->GetForwardVector() * TargetComponent->GetTraceLength();
}



/*
* Action Pressed
*/
void APlayerCharacter::AttackButtonPressed()
{
	if (CombatComponent)
		CombatComponent->RequestAttack(EAttackType::EAT_NormalAttack);
}
void APlayerCharacter::ChargeAttackButtonPressed()
{
	if (CombatComponent)
	{
		CombatComponent->RequestAttack(EAttackType::EAT_ChargeAttack);
	}
}
void APlayerCharacter::RollButtonPressed()
{
	if (CombatComponent)
	{
		CombatComponent->RequestRoll();
	}
}
void APlayerCharacter::TargetButtonPressed()
{
	if (TargetComponent == nullptr)
	{
		return;
	}

	if (TargetComponent->IsTargeting())
	{
		TargetComponent->UnFocus();
	}
	else
	{
		TargetComponent->RequestFocus();
	}
}

void APlayerCharacter::GuardButtonPressed()
{
	if (CombatComponent)
	{
		CombatComponent->RequestGuard();
	}
}

void APlayerCharacter::TestDeflectButtonPressed()
{
	PlayAnimMontage(SwordDeflectMontage);
}
/*
* Axes
*/
void APlayerCharacter::MoveForward(float Value)
{
	const FRotator& ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}
void APlayerCharacter::MoveRight(float Value)
{
	const FRotator& ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControlRotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
void APlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
void APlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

