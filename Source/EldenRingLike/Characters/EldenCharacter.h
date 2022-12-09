
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EldenRingLike/Interfaces/TargetInterface.h"
#include "EldenRingLike/Interfaces/TargetedInterface.h"
#include "EldenCharacter.generated.h"

class UCombatComponent;
class UTargetComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ELDENRINGLIKE_API AEldenCharacter : public ACharacter, public ITargetInterface, public ITargetedInterface
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
	virtual void Landed(const FHitResult& Hit) override;



	/*
	* Target Interface
	*/
	virtual FVector GetLocation() override;
	virtual FVector GetCameraDirection() override;
	virtual void SetupTarget(const bool& bDoTarget) override;
	virtual void SetControllerRotation(const FRotator& NewRotation) override;
	virtual float GetDistanceTo(const AActor* OtherActor) override;
	virtual bool IsTargeting() override;
	/*
	* Targeted Interface
	*/
	virtual FVector GetTargetLocation() override;
	

protected:
	void BeginPlay() override;

	/*
	* Actions
	* Pressed
	*/
	virtual void Jump() override;
	void AttackButtonPressed();
	void RollButtonPressed();
	void TargetButtonPressed();

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

	UPROPERTY(VisibleAnywhere)
	UTargetComponent* TargetComponent;

	UPROPERTY(EditAnywhere, Category = TargetedProperties)
	FName TargetSocketName;
public:	


};
