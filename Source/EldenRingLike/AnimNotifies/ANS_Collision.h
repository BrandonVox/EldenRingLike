
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"
#include "ANS_Collision.generated.h"



UCLASS()
class ELDENRINGLIKE_API UANS_Collision : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UANS_Collision();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation, float TotalDuration,
		const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation, float FrameDeltaTime,
		const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY()
	TScriptInterface<IAttackInterface> AttackObject;
};
