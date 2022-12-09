// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateCharacterAnimNotifyState.h"
#include "EldenRingLike/Characters/EldenCharacter.h"



void URotateCharacterAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}
	AEldenCharacter* EldenCharacter = Cast<AEldenCharacter>(MeshComp->GetOwner());
	if (EldenCharacter)
	{
		EldenCharacter->RotateCharacter(FrameDeltaTime);
	}
}
