// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboAnimNotify.h"
#include "EldenRingLike/Characters/EldenCharacter.h"


void UComboAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	if (MeshComp == nullptr)
	{
		return;
	}
	AEldenCharacter* EldenCharacter = Cast<AEldenCharacter>(MeshComp->GetOwner());
	if (EldenCharacter)
	{
		EldenCharacter->Combo();
	}
}
