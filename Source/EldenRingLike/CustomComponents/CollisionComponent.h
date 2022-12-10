// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EldenRingLike/Interfaces/AttackInterface.h"
#include "CollisionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHitActorDelegate, const FHitResult&, HitResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ELDENRINGLIKE_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCollisionComponent();


	void ClearHittedActors();
	void DetectHit();

	UPROPERTY()
	FHitActorDelegate HitActorDelegate;

protected:
	virtual void BeginPlay() override;


private:
	IAttackInterface* AttackableObject = nullptr;



	UPROPERTY()
	TArray<AActor*> HittedActors;

	UPROPERTY(EditAnywhere)
	float TraceRadius = 20.f;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditAnywhere)
	bool bDebug;

public:
	FORCEINLINE void SetAttackableObject(IAttackInterface* Value) { AttackableObject = Value; }
};
