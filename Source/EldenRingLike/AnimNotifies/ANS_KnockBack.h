// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EldenRingLike/Interfaces/GuardInterface.h"
#include "ANS_KnockBack.generated.h"


UCLASS()
class ELDENRINGLIKE_API UANS_KnockBack : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation, float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY()
	TScriptInterface<IGuardInterface> GuardObject;

	UPROPERTY(EditAnywhere)
	float AmmountKnockBackInOneSecond = 80.f;
};
