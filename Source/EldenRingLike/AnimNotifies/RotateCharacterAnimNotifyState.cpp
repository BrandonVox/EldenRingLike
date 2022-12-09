// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateCharacterAnimNotifyState.h"
#include "EldenRingLike/Characters/EldenCharacter.h"

void URotateCharacterAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	// Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

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
