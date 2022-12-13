// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateCharacterAnimNotifyState.h"


void URotateCharacterAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(!AttackObject)
		if(MeshComp)
			AttackObject = TScriptInterface<IAttackInterface>(MeshComp->GetOwner());
	

	if (AttackObject)
		AttackObject->RotateCharacter(FrameDeltaTime);
}
