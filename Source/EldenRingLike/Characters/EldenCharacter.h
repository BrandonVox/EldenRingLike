
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EldenRingLike/Interfaces/TargetInterface.h"
#include "EldenRingLike/Interfaces/TargetedInterface.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"
#include "EldenRingLike/Interfaces/GuardInterface.h"
#include "EldenCharacter.generated.h"

class UEldenAnimInstance;

class UCombatComponent;
class UTargetComponent;
class UCollisionComponent;

UCLASS()
class ELDENRINGLIKE_API AEldenCharacter : 
	public ACharacter, 
	public ITargetInterface, 
	public ITargetedInterface,
	public IAttackInterface,
	public IGuardInterface
{
	GENERATED_BODY()

public:
	AEldenCharacter();
	virtual void PostInitializeComponents() override;
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;
	bool IsAttacking() const;
	bool IsDefending() const;
	/*
	* Anim Notifies
	*/
	void ResetCombat();
	/*
	* Target Interface
	*/
	virtual FVector GetLocation() override;
	virtual FVector EndLocationToFindTarget() override;
	virtual void StartFocusing(const bool& bDoTarget) override;

	virtual float GetDistanceTo_Custom(AActor* OtherActor) override;
	virtual bool IsTargeting() override;
	virtual bool IsRolling() override;

	virtual FRotator GetControllerRotation() override;
	virtual FRotator GetObjectRotation() override;
	virtual FRotator ControllerYawRotation() override;
	virtual void SetControllerRotation(const FRotator& NewRotation) override;
	virtual void SetObjectRotation(const FRotator& NewRotation) override;
	/*
	* Targeted Interface
	*/
	virtual FVector GetTargetLocation() override;
	/*
	* Attack Interface
	*/
	virtual void RotateCharacter(const float& DeltaTime) override;

	virtual void Combo() override;
	virtual void ChargeAttack() override;
	virtual FVector StartHitLocation() override;
	virtual FVector EndHitLocation() override;
	virtual void SetupHitDetection() override;
	virtual void DetectHit() override;
	/*
	* Guard Interface
	*/
	virtual void EndGuard() override;
	virtual void KnockBack(const float& Ammount) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHitActor(const FHitResult& HitResult);

	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
		FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
		FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	/*
	* Guard
	*/
	void Guard();
	void UnGuard();

private:
	void HandleHitted(const FVector& HitLocation, const FVector& ShotFromDirection);

	void StopAllMontages(const float& BlendOutSeconds = 0.3f);

protected:
	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere)
	UCombatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere)
	UTargetComponent* TargetComponent;
	UPROPERTY(VisibleAnywhere)
	UCollisionComponent* CollisionComponent;
	/*
	* Sword Deflect
	*/
	UPROPERTY(EditAnywhere, Category = Hitted)
	USoundBase* SwordDeflectSound;
	UPROPERTY(EditAnywhere, Category = Hitted)
	UParticleSystem* SwordDeflectImpact;
	UPROPERTY(EditAnywhere, Category = Hitted)
	UAnimMontage* SwordDeflectMontage;
	/*
	* Elden Animinstance
	*/
	UPROPERTY()
	UEldenAnimInstance* EldenAnimInstance;
	/*
	* Movement
	*/
	float DefaultMaxWalkSpeed = 700.f;
private:

	
	UPROPERTY(EditAnywhere, Category = TargetedProperties)
	FName TargetSocketName;
	/*
	* Hit Detection
	*/
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

	/*
	* Guard
	*/
	UPROPERTY(EditAnywhere, Category = Guard)
	UAnimMontage* EndGuardMontage;
	UPROPERTY(EditAnywhere, Category = Guard)
	UAnimMontage* GuardReactMontage;

	UPROPERTY()
	FVector LastEnemyAttackDirection;

public:	
};
