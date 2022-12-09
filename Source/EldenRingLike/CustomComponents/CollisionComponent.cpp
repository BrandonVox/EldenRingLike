

#include "CollisionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SceneComponent.h" // dont known this

UCollisionComponent::UCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AttackableObject == nullptr)
	{
		AttackableObject = Cast<IAttackInterface>(GetOwner());
	}

	if (GetOwner())
	{
		ActorsToIgnore.Emplace(GetOwner());
	}
}

void UCollisionComponent::ClearHittedActors()
{
	HittedActors.Empty();
}

void UCollisionComponent::DetectHit()
{
	if (AttackableObject == nullptr)
	{
		return;
	}

	TArray<FHitResult> HitResults;

	// Start of Sword -> End of Sword
	bool bHitSomething = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetOwner(),
		AttackableObject->StartHitLocation(),
		AttackableObject->EndHitLocation(),
		TraceRadius,
		TraceObjectTypes,
		true,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResults,
		true
	);

	//if (bHitSomething)
	//{
	//	for (FHitResult HR : HitResults)
	//	{
	//		if (HR.bBlockingHit)
	//		{
	//			if (HR.GetActor())
	//			{
	//				// Luu vao mang Hitted Actors
	//				if (HittedActors.Contains(HR.GetActor()) == false)
	//				{
	//					HittedActors.Emplace(HR.GetActor());
	//					HitActorDelegate.Broadcast(HR);
	//				}
	//			}
	//		}
	//	}
	//}


}

