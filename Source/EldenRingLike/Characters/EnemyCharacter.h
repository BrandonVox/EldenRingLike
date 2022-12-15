// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EldenCharacter.h"
#include "EnemyCharacter.generated.h"


class AAIController;
class AActor;

UCLASS()
class ELDENRINGLIKE_API AEnemyCharacter : public AEldenCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void Tick(float DeltaTime) override;
	/*
	* Targeted Interface
	*/
	virtual void FocusBack(AActor* TargetActor) override;
	virtual void UnTargeted() override;

protected:
	virtual void BeginPlay() override;

private:
	void DelayGuardTimerFinished();
	bool CloseEnoughToPlayer();
	void MoveToPlayer();

private:
	UPROPERTY()
	AAIController* AIController;
	/*
	* Test
	*/
	UPROPERTY()
	FTimerHandle GuardDelayTimer;

	UPROPERTY(EditAnywhere, Category = Test)
	float GuardDelaySeconds = 2.f;

	bool bMoveToPlayer = false;
	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackableRadius = 110.f;

	// change
	UPROPERTY()
	AActor* PlayerActor;
};
