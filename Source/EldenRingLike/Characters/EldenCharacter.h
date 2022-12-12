
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
	virtual void PostInitializeComponents() override;
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;
	/*
	* Anim Notifies
	*/
	void RotateCharacter(const float& DeltaTime); 
	void ResetCombat();
	/*
	* Target Interface
	*/
	virtual FVector GetLocation() override;
	virtual FVector EndLocationToFindTarget() override;
	virtual void SetupTarget(const bool& bDoTarget) override;

	virtual float GetDistanceTo(const AActor* OtherActor) override;
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
	virtual void Combo() override;
	virtual void ChargeAttack() override;
	virtual FVector StartHitLocation() override;
	virtual FVector EndHitLocation() override;
	virtual void SetupHitDetection() override;
	virtual void DetectHit() override;
	

protected:
	void BeginPlay() override;

	


	UFUNCTION()
	virtual void OnHitActor(const FHitResult& HitResult);

	UFUNCTION()
	virtual void OnTakeDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
		FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
		FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

private:
	void HandleHitted(const FVector& HitLocation, const FVector& ShotFromDirection);
	const bool IsAttacking();
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

public:	
};
