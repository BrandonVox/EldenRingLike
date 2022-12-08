// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetCombatAnimNotify.h"

#include "Components/SkeletalMeshComponent.h"
#include "EldenRingLike/Characters/EldenCharacter.h"

void UResetCombatAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp == nullptr)
	{
		return;
	}
	AEldenCharacter* EldenCharacter = Cast<AEldenCharacter>(MeshComp->GetOwner());
	if (EldenCharacter)
	{
		EldenCharacter->ResetCombat();
	}
}
