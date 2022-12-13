

#include "ANS_Collision.h"

UANS_Collision::UANS_Collision()
{
	NotifyColor = FColor::Red;
}

void UANS_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp)
		return;

	AttackObject = TScriptInterface<IAttackInterface>(MeshComp->GetOwner());

	if (AttackObject)
		AttackObject->SetupHitDetection();

}

void UANS_Collision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!AttackObject)
		if (MeshComp)
			AttackObject = TScriptInterface<IAttackInterface>(MeshComp->GetOwner());

	if (AttackObject)
		AttackObject->DetectHit();
}
