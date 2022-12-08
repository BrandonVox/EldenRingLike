

#include "CombatComponent.h"
#include "GameFramework/Character.h" // Character

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Character == nullptr)
	{
		Character = Cast<ACharacter>(GetOwner());
	}
}

//void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

void UCombatComponent::RequestAttack()
{
	if (CombatState == ECombatState::ECS_Attack)
	{
		bIsSavingAttack = true;
		return;
	}

	if (CanAttack())
	{
		Attack();
	}
}

bool UCombatComponent::CanAttack()
{
	return 
		CombatState == ECombatState::ECS_Free 
		&& NormalAttackMontages.IsEmpty() == false;
}

bool UCombatComponent::CanCombo()
{
	return NormalAttackMontages.IsEmpty() == false;
}

// Reach Combo Anim Notify
void UCombatComponent::Combo()
{
	if (bIsSavingAttack)
	{
		bIsSavingAttack = false;
		if (CanCombo())
		{
			Attack();
		}
	}
}

void UCombatComponent::ResetCombat()
{
	CombatState = ECombatState::ECS_Free;
	AttackIndex = 0;
	bIsSavingAttack = false;
}

void UCombatComponent::Attack()
{
	if (Character == nullptr)
	{
		return;
	}

	if (AttackIndex > NormalAttackMontages.Num() - 1)
	{
		AttackIndex = 0;
	}
	UAnimMontage* MontageToPlay = NormalAttackMontages[AttackIndex];
	if (MontageToPlay)
	{
		Character->PlayAnimMontage(MontageToPlay);
		CombatState = ECombatState::ECS_Attack;
		AttackIndex ++;
	}
}

