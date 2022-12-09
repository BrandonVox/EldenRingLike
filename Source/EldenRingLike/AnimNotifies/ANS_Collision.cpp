

#include "ANS_Collision.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"

UANS_Collision::UANS_Collision()
{
	NotifyColor = FColor::Red;
}

void UANS_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp == nullptr)
		return;

	IAttackInterface* AttackableObject = Cast<IAttackInterface>(MeshComp->GetOwner());
	if (AttackableObject)
	{
		AttackableObject->SetupHitDetection();
	}
}

void UANS_Collision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp == nullptr)
		return;

	IAttackInterface* AttackableObject = Cast<IAttackInterface>(MeshComp->GetOwner());
	if (AttackableObject)
	{
		AttackableObject->DetectHit();
	}
}
