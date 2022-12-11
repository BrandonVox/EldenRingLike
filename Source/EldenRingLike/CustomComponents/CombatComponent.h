
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
	void RequestRoll();



	void Combo();
	void ResetCombat();
	void RotateCharacter(const float& DeltaTime);

	void ChargeAttack();

	const bool IsAttacking_Air();
	const bool IsAttacking_ChargeAttack();

protected:
	virtual void BeginPlay() override;

private:
	bool CanAttack();
	bool CanCombo();
	bool CanRoll();
	bool IsInAir();
	void Attack(EAttackType AttackType);
	void PlayAnimMontage(UAnimMontage* MontageToPlay);
	void Roll();
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

	UPROPERTY(EditAnywhere, Category = Attack)
	TArray<UAnimMontage*> NormalAttackMontages;

	UPROPERTY(EditAnywhere, Category = Attack)
	TArray<UAnimMontage*> AirAttackMontages;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* StartChargeAttackMontage;


	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* ChargeAttackMontage;

	UPROPERTY(EditAnywhere, Category = Roll)
	UAnimMontage* RollMontage;

	UPROPERTY(EditAnywhere, Category = Roll)
	float RotateSpeed;

public:
	/*
	* Getters
	*/
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }
	FORCEINLINE void SetCombatState(const ECombatState& Value) { CombatState = Value; }

	/*
	* Setters
	*/
	FORCEINLINE const bool IsAttacking() { return CombatState == ECombatState::ECS_Attack; }
	FORCEINLINE const bool IsRolling() { return CombatState == ECombatState::ECS_Roll; }
};
