

#include "TargetComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FocusObject == nullptr)
	{
		FocusObject = Cast<ITargetInterface>(GetOwner());
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
		LookTarget(DeltaTime);
	}
}

void UTargetComponent::RequestFocus()
{
	FindTarget();
}

void UTargetComponent::FindTarget()
{
	// sphere trace de tim muc tieu
	if (FocusObject == nullptr)
	{
		return;
	}

	FHitResult HitResult;

	const FVector StartLocation = FocusObject->GetLocation();
	FVector EndLocation = FocusObject->EndLocationToFindTarget();

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
		TargetObject = Cast<ITargetedInterface>(HitResult.GetActor());
		if (TargetObject)
		{
			FocusObject->StartFocusing(true);
			ObjectRotation = FocusObject->GetObjectRotation();
			ControllerRotation = FocusObject->GetControllerRotation();
			bIsTargeting = true;
			//
			TargetObject->FocusBack(GetOwner());
		}
	}
}

// EnemyCharacter
void UTargetComponent::FocusBack(AActor* EnemyActor)
{
	TargetObject = Cast<ITargetedInterface>(EnemyActor);
	if (FocusObject && TargetObject)
	{
		FocusObject->StartFocusing(true);
		ObjectRotation = FocusObject->GetObjectRotation();
		ControllerRotation = FocusObject->GetControllerRotation();
		bIsTargeting = true;
	}
}

void UTargetComponent::UnFocus()
{
	bIsTargeting = false;
	if(FocusObject)
		FocusObject->StartFocusing(false);

	if(TargetObject)
		TargetObject->UnTargeted();
	TargetObject = nullptr;
}

// EnemyCharacter.h
void UTargetComponent::UnTargeted()
{
	bIsTargeting = false;
	FocusObject->StartFocusing(false);
	TargetObject = nullptr;
}

void UTargetComponent::LookTarget(const float& DeltaTime)
{
	if (FocusObject == nullptr)
	{
		return;
	}

	if (TargetObject == nullptr)
	{
		return;
	}

	// get actor location
	FVector StartLocation = FocusObject->GetLocation();
	StartLocation.Z += Offset_Z;

	// get location to target
	FVector EndLocation = TargetObject->GetTargetLocation();

	FRotator TargetControllerRotation = (EndLocation - StartLocation).Rotation();

	ControllerRotation = FMath::RInterpTo(ControllerRotation,
		TargetControllerRotation, DeltaTime, ControllerRotateSpeed);

	FocusObject->SetControllerRotation(ControllerRotation);

	
	if (FocusObject->IsRolling() == false)
	{
		ObjectRotation = FMath::RInterpTo(
			FocusObject->GetObjectRotation(),
			FocusObject->ControllerYawRotation(),
			DeltaTime,
			ObjectRotateSpeed);

		FocusObject->SetObjectRotation(ObjectRotation);
	}


}