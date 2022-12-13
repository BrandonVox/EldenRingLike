

#include "CombatComponent.h"
#include "GameFramework/Character.h" // Character
#include "GameFramework/CharacterMovementComponent.h" // Character.GetCharacterMovement()
#include "Kismet/KismetMathLibrary.h" //
#include "EldenRingLike/Interfaces/TargetInterface.h"

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

/*
* Attack
*/
void UCombatComponent::RequestAttack(const EAttackType& AttackType)
{
	if (CombatState == ECombatState::ECS_Attack)
	{
		SaveAttackType = AttackType;
		bIsSavingAttack = true;
		return;
	}

	if (CanAttack())
	{
		Attack(AttackType);
	}
}

bool UCombatComponent::CanAttack()
{
	return CombatState == ECombatState::ECS_Free;
}

void UCombatComponent::Attack(EAttackType AttackType)
{

	// override attack type if is in air
	if (AttackType == EAttackType::EAT_NormalAttack && IsInAir())
	{
		AttackType = EAttackType::EAT_AirAttack;
	}

	UAnimMontage* MontageToPlay = GetAttackMontage(AttackType);
	if (MontageToPlay)
	{
		PlayAnimMontage(MontageToPlay);
		CombatState = ECombatState::ECS_Attack;
		LastAttackType = AttackType;
		AttackIndex++;
	}
}

/*
* Guard
*/
void UCombatComponent::RequestGuard()
{
	if (CanGuard())
	{
		Guard();
	}
}

bool UCombatComponent::CanGuard()
{
	return CombatState == ECombatState::ECS_Free;
}

void UCombatComponent::Guard()
{
	if (StartGuardMontage)
	{
		PlayAnimMontage(StartGuardMontage);
		CombatState = ECombatState::ECS_Guard;
	}
}

void UCombatComponent::ToggleGuard(const bool& bGuard)
{
	if (bGuard)
	{
		CombatState = ECombatState::ECS_Guard;
	}
	else
	{
		ResetCombat();
	}
}

void UCombatComponent::RequestRoll()
{
	if (CombatState == ECombatState::ECS_Roll)
	{
		bIsSavingRoll = true;
		return;
	}

	if (CanRoll())
	{
		Roll(); 
	}
}



bool UCombatComponent::CanRoll()
{
	return
		CombatState == ECombatState::ECS_Free 
		|| CombatState == ECombatState::ECS_Attack
		|| CombatState == ECombatState::ECS_Guard;
}

bool UCombatComponent::IsInAir()
{
	return Character
		&& Character->GetCharacterMovement()
		&& Character->GetCharacterMovement()->IsFalling();
}

// Reach Combo Anim Notify
// Perform Save Attack
void UCombatComponent::Combo()
{
	if (bIsSavingAttack)
	{
		bIsSavingAttack = false;
		if (CanCombo())
		{
			Attack(SaveAttackType);
		}
	}
}

bool UCombatComponent::CanCombo()
{
	return true;
}

void UCombatComponent::ResetCombat()
{

	CombatState = ECombatState::ECS_Free;
	AttackIndex = 0;
	bIsSavingAttack = false;
	LastAttackType = EAttackType::EAT_NormalAttack;
	SaveAttackType = EAttackType::EAT_NormalAttack;


	if (bIsSavingRoll)
	{
		bIsSavingRoll = false;
		if (CanRoll())
		{
			Roll();
		}
	}
	
}

void UCombatComponent::HandleFinishRoll()
{
	/*
	* if character is targeting
	* rotate along controller
	*/
	if (Character == nullptr)
	{
		return;
	}

	ITargetInterface* TargetableCharacter = Cast<ITargetInterface>(Character);
	if (TargetableCharacter && TargetableCharacter->IsTargeting())
	{
		Character->bUseControllerRotationYaw = true;
	}
	
}




void UCombatComponent::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	if (Character)
	{
		Character->PlayAnimMontage(MontageToPlay);
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

void UCombatComponent::ChargeAttack()
{
	PlayAnimMontage(ChargeAttackMontage); 
}

const bool UCombatComponent::IsAttacking_Air()
{
	return IsAttacking() && LastAttackType == EAttackType::EAT_AirAttack;
}

const bool UCombatComponent::IsAttacking_ChargeAttack()
{
	return IsAttacking() && LastAttackType == EAttackType::EAT_ChargeAttack;
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

UAnimMontage* UCombatComponent::GetAttackMontage(const EAttackType& AttackType)
{
	if (LastAttackType != AttackType)
	{
		AttackIndex = 0;
	}

	switch (AttackType)
	{
	case EAttackType::EAT_NormalAttack:
		if (NormalAttackMontages.IsEmpty())
		{
			return nullptr;
		}
		if (AttackIndex > NormalAttackMontages.Num() - 1)
		{
			AttackIndex = 0;
		}
		return NormalAttackMontages[AttackIndex];

	case EAttackType::EAT_AirAttack:
		if (AirAttackMontages.IsEmpty())
		{
			return nullptr;
		}
		if (AttackIndex > AirAttackMontages.Num() - 1)
		{
			AttackIndex = 0;
		}
		return AirAttackMontages[AttackIndex];

	case EAttackType::EAT_ChargeAttack:
		return StartChargeAttackMontage;
	}

	return nullptr;
}


