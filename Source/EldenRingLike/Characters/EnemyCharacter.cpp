

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

	if (CloseEnoughToPlayer())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("close to player"));
		if (CombatComponent)
			CombatComponent->RequestAttack(EAttackType::EAT_NormalAttack);
	}
	else
		MoveToPlayer();
}

bool AEnemyCharacter::CloseEnoughToPlayer()
{
	// change
	if (PlayerActor == nullptr)
		return false;

	return GetDistanceTo(PlayerActor) <= AttackableRadius;
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
		/*
		* change
		*/
		PlayerActor = TargetActor;
	}
}

void AEnemyCharacter::UnTargeted()
{
	if (TargetComponent)
	{
		TargetComponent->UnTargeted();
	}
}