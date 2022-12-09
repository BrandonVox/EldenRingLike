

#include "TargetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TargetableObject == nullptr)
	{
		TargetableObject = Cast<ITargetInterface>(GetOwner());
	}

	if (GetOwner())
	{
		ActorsToIgnore.Emplace(GetOwner());
	}
}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsTargeting)
	{
		LookTarget();
	}
}


void UTargetComponent::FindTarget()
{
	// sphere trace de tim muc tieu
	if (GetOwner() == nullptr)
	{
		return;
	}

	FHitResult HitResult;

	const FVector StartLocation = TargetableObject->GetLocation();
	FVector EndLocation =
		StartLocation + TargetableObject->GetCameraDirection() * TraceLength;

	// Start of Sword -> End of Sword
	bool bDoHit = UKismetSystemLibrary::SphereTraceSingleForObjects
	(
		GetOwner(),
		StartLocation,
		EndLocation,
		TraceRadius,
		TraceObjectTypes,
		true,
		ActorsToIgnore,
		bDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult,
		true
	);


	if (bDoHit)
	{

		TargetedObject = Cast<ITargetedInterface>(HitResult.GetActor());
		if (TargetedObject)
		{
			TargetableObject->SetupTarget(true);
			bIsTargeting = true;
		}

	}


}


void UTargetComponent::Target()
{
	FindTarget();
}

void UTargetComponent::UnTarget()
{
	bIsTargeting = false;
	TargetableObject->SetupTarget(false);
	TargetedObject = nullptr;
}


void UTargetComponent::LookTarget()
{
	// huong camera den muc tieu
	//if (TargetCharacter == nullptr)
	//{
	//	UnTarget();
	//	return;
	//}

	if (TargetableObject == nullptr)
	{
		// UnTarget();
		return;
	}

	if (TargetedObject == nullptr)
	{
		return;
	}

	FVector StartLocation = TargetableObject->GetLocation();
	StartLocation.Z += Offset_Z;

	FVector EndLocation = TargetedObject->GetTargetLocation();

	FRotator NewControllerRotation = (EndLocation - StartLocation).Rotation();

	TargetableObject->SetControllerRotation(NewControllerRotation);


	// neu khoang cach tu nguoi choi den 
	// muc tieu qua xa thi khong cho target nua
	//const float DistanceToTarget = TargetableObject->GetDistanceTo(TargetCharacter);

	//if (DistanceToTarget > MaxTargetLength)
	//{
	//	UnTarget();
	//}
}