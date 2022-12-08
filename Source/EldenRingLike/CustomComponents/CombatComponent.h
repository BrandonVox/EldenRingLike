
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

	void RequestAttack();



	void Combo();
	void ResetCombat();

protected:
	virtual void BeginPlay() override;

	virtual void Attack();

private:
	bool CanAttack();
	bool CanCombo();

private:
	UPROPERTY()
	ACharacter* Character;




	UPROPERTY()
	ECombatState CombatState = ECombatState::ECS_Free;
	int16 AttackIndex = 0;
	bool bIsSavingAttack = false;



	UPROPERTY(EditAnywhere, Category = Attack)
		TArray<UAnimMontage*> NormalAttackMontages;


public:	
	FORCEINLINE void SetCharacter(ACharacter* Value) { Character = Value; }
		
};
