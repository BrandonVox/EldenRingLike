// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_FinishCharge.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"

void UAN_FinishCharge::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	IAttackInterface* AttackObject = Cast<IAttackInterface>(MeshComp->GetOwner());
	if (AttackObject)
	{
		AttackObject->ChargeAttack();
	}

}
