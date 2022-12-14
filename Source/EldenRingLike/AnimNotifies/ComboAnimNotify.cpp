// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboAnimNotify.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"


void UComboAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	IAttackInterface* AttackObject = Cast<IAttackInterface>(MeshComp->GetOwner());
	if (AttackObject)
	{
		AttackObject->Combo();
	}

}
