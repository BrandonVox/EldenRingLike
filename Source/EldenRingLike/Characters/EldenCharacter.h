
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EldenCharacter.generated.h"

class UCombatComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ELDENRINGLIKE_API AEldenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEldenCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	// virtual void Tick(float DeltaTime) override;
	void Combo();
	void ResetCombat();
	void RotateCharacter(const float& DeltaTime);


protected:
	void BeginPlay() override;

	/*
	* Actions
	* Pressed
	*/
	void AttackButtonPressed();
	void RollButtonPressed();

	// Axes
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComponent;
public:	


};
