

#include "EnemyCharacter.h"
#include "EldenRingLike/CustomComponents/TargetComponent.h"
#include "EldenRingLike/CustomComponents/CombatComponent.h"

/*
* Targeted Interface
*/
void AEnemyCharacter::FocusBack(AActor* EnemyActor)
{
	if (TargetComponent)
	{
		TargetComponent->FocusBack(EnemyActor);
	}
}
void AEnemyCharacter::UnTargeted()
{
	if (TargetComponent)
	{
		TargetComponent->UnTargeted();
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();


	Guard();
	//if (CombatComponent)
	//{
	//	CombatComponent->RequestGuard();

	//	GetWorldTimerManager().SetTimer(
	//		GuardDelayTimer,
	//		this,
	//		&AEnemyCharacter::DelayGuardTimerFinished,
	//		GuardDelaySeconds
	//	);
	//}
}

void AEnemyCharacter::DelayGuardTimerFinished()
{
	CombatComponent->RequestGuard();

	GetWorldTimerManager().SetTimer(
		GuardDelayTimer,
		this,
		&AEnemyCharacter::DelayGuardTimerFinished,
		GuardDelaySeconds
	);
}
