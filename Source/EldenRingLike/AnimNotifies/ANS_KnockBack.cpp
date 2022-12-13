// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_KnockBack.h"


void UANS_KnockBack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!GuardObject)
		if (MeshComp)
			GuardObject = TScriptInterface<IGuardInterface>(MeshComp->GetOwner());
	
	if(GuardObject)
		GuardObject->KnockBack(AmmountKnockBackInOneSecond * FrameDeltaTime);
}
