
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EldenRingLike/Interfaces/TargetInterface.h"
#include "EldenRingLike/Interfaces/TargetedInterface.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"
#include "EldenCharacter.generated.h"

class UCombatComponent;
class UTargetComponent;
class UCollisionComponent;

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ELDENRINGLIKE_API AEldenCharacter : 
	public ACharacter, 
	public ITargetInterface, 
	public ITargetedInterface,
	public IAttackInterface
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

	/*
	* Attack Interface
	*/
	virtual FVector StartHitLocation() override;
	virtual FVector EndHitLocation() override;
	virtual void SetupHitDetection() override;
	virtual void DetectHit() override;
	

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


	UFUNCTION()
	virtual void OnHitActor(const FHitResult& HitResult);

	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
		FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
		FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

private:
	void HandleHitted(const FVector& HitLocation, const FVector& ShotFromDirection);
private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere)
	UTargetComponent* TargetComponent;

	UPROPERTY(VisibleAnywhere)
	UCollisionComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = TargetedProperties)
	FName TargetSocketName;


	UPROPERTY(EditAnywhere, Category = HitDetection)
	FName StartHitSocket;
	UPROPERTY(EditAnywhere, Category = HitDetection)
	FName EndHitSocket;


	/*
	* Hitted
	*/
	UPROPERTY(EditAnywhere, Category = Hitted)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Hitted)
	UParticleSystem* HitImpact;

	UPROPERTY(EditAnywhere, Category = Hitted)
	UAnimMontage* HitMontage_Front;

public:	


};
