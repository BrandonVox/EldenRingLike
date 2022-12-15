

#include "EnemyCharacter.h"
#include "EldenRingLike/CustomComponents/TargetComponent.h"
#include "EldenRingLike/CustomComponents/CombatComponent.h"

#include "AIController.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// look
	AIController = Cast<AAIController>(GetController());

	// Guard();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	// change, xem thu class cha co phai la character khong?
	Super::Tick(DeltaTime);
}

bool AEnemyCharacter::CloseEnoughToPlayer()
{
	if(PlayerActor)
		return GetDistanceTo(PlayerActor) <= AttackableRadius;
	return false;
}

void AEnemyCharacter::MoveToPlayer()
{
	if (!PlayerActor || !AIController)
		return;
	FAIMoveRequest MoveRequest;

	MoveRequest.SetGoalActor(PlayerActor);
	MoveRequest.SetAcceptanceRadius(AttackableRadius - 75.f);
	AIController->MoveTo(MoveRequest);
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

/*
* Targeted Interface
*/
void AEnemyCharacter::FocusBack(AActor* TargetActor)
{
	if (TargetComponent)
	{
		TargetComponent->FocusBack(TargetActor);
		MoveToPlayer();
	
	}
}

void AEnemyCharacter::UnTargeted()
{
	if (TargetComponent)
	{
		TargetComponent->UnTargeted();
	}
}