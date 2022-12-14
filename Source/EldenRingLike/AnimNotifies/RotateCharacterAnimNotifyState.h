// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"
#include "RotateCharacterAnimNotifyState.generated.h"



UCLASS()
class ELDENRINGLIKE_API URotateCharacterAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation, float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackObject;



};
