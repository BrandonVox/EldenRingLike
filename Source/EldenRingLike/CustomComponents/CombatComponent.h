
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EldenRingLike/Types/Types.h"
#include "CombatComponent.generated.h"

class ACharacter;
class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDENRINGLIKE_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RequestAttack(const EAttackType& AttackType);
	void RequestGuard();
	void RequestRoll();



	void Combo();
	void ResetCombat();
	void RotateCharacter(const float& DeltaTime);

	void ChargeAttack();

	const bool IsAttacking_Air();
	const bool IsAttacking_ChargeAttack();



	/*
	* Guard
	*/
	bool CanGuard();
	void ToggleGuard(const bool& bGuard);


protected:
	virtual void BeginPlay() override;

private:
	/*
	* Attack
	*/
	bool CanAttack();
	void Attack(EAttackType AttackType);
	bool CanCombo();
	/*
	* Guard
	*/
	void Guard();
	/*
	* Roll
	*/
	bool CanRoll();
	void Roll();

	bool IsInAir();
	void PlayAnimMontage(UAnimMontage* MontageToPlay);
	void HandleFinishRoll();
	FRotator GetRollRotation();
	UAnimMontage* GetAttackMontage(const EAttackType& AttackType);


private:
	UPROPERTY()
	ACharacter* Character;

	ECombatState CombatState = ECombatState::ECS_Free;
	int16 AttackIndex = 0;
	bool bIsSavingAttack = false;
	bool bIsSavingRoll = false;

	EAttackType LastAttackType = EAttackType::EAT_NormalAttack;
	EAttackType SaveAttackType = EAttackType::EAT_NormalAttack;

	/*
	* Attack Montages
	*/
	UPROPERTY(EditAnywhere, Category = Attack)
	TArray<UAnimMontage*> NormalAttackMontages;

	UPROPERTY(EditAnywhere, Category = Attack)
	TArray<UAnimMontage*> AirAttackMontages;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* StartChargeAttackMontage;


	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* ChargeAttackMontage;

	/*
	* Guard
	*/
	UPROPERTY(EditAnywhere, Category = Guard)
	UAnimMontage* GuardMontage;

	/*
	* Roll
	*/
	UPROPERTY(EditAnywhere, Category = Roll)
	UAnimMontage* RollMontage;

	UPROPERTY(EditAnywhere, Category = Roll)
	float RotateSpeed;

public:
	/*
	* Setters
	*/
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }
	FORCEINLINE void SetCombatState(const ECombatState& Value) { CombatState = Value; }

	/*
	* Getters
	*/
	FORCEINLINE bool IsAttacking() const { return CombatState == ECombatState::ECS_Attack; }
	FORCEINLINE bool IsDefending() const { return CombatState == ECombatState::ECS_Guard; }
	FORCEINLINE bool IsRolling() const {  return CombatState == ECombatState::ECS_Roll; }
};
