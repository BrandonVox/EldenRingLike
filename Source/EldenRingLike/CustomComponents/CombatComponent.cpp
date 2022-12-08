

#include "CombatComponent.h"
#include "GameFramework/Character.h" // Character
#include "GameFramework/CharacterMovementComponent.h" // Character.GetCharacterMovement()
#include "Kismet/KismetMathLibrary.h" //

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

void UCombatComponent::RequestRoll()
{
	if (CanRoll())
	{
		Roll(); 
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

bool UCombatComponent::CanRoll()
{
	// Character is in air -> false
	if (Character 
		&& Character->GetCharacterMovement() 
		&& Character->GetCharacterMovement()->IsFalling())
	{
		return false;
	}
	
	return
		CombatState == ECombatState::ECS_Free 
		|| CombatState == ECombatState::ECS_Attack;
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

void UCombatComponent::Roll()
{
	if (Character == nullptr)
	{
		return;
	}

	if (RollMontage)
	{
		Character->PlayAnimMontage(RollMontage);
		CombatState = ECombatState::ECS_Roll;
	}
}

void UCombatComponent::RotateCharacter(const float& DeltaTime)
{
	if (Character == nullptr )
	{
		return;
	}
	
	FRotator RollRotation = GetRollRotation();
	RollRotation = FMath::RInterpTo(Character->GetActorRotation(), RollRotation, DeltaTime, RotateSpeed);
	Character->SetActorRotation(RollRotation);
}

FRotator UCombatComponent::GetRollRotation()
{
	if (!Character || !Character->GetCharacterMovement())
	{
		return FRotator();
	}

	FRotator RollRotation;
	if (Character->GetCharacterMovement()->GetLastInputVector().Size() > 0.f)
	{
		RollRotation = UKismetMathLibrary::MakeRotFromX(Character->GetLastMovementInputVector());
	}
	else
	{
		RollRotation = Character->GetActorRotation();
	}

	return RollRotation;
}


