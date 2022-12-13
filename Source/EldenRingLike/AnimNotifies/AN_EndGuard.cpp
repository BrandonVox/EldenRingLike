// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_EndGuard.h"
#include "EldenRingLike/Interfaces/GuardInterface.h"

void UAN_EndGuard::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	IGuardInterface* GuardObject = Cast<IGuardInterface>(MeshComp->GetOwner());
	if (GuardObject)
	{
		GuardObject->EndGuard();
	}
}
