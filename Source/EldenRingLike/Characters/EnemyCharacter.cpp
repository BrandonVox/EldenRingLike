

#include "EnemyCharacter.h"
#include "EldenRingLike/CustomComponents/TargetComponent.h"


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
